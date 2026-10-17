import asyncio
from signal import SIGTERM
shutdown_event = asyncio.Event()

async def service():
    try:
        while not shutdown_event.is_set():
            print("Hop hop hop hop")
            await asyncio.sleep(2)
    except asyncio.CancelledError:
        print("Cleanup")
        raise

async def main():
    loop = asyncio.get_running_loop()
    loop.add_signal_handler(SIGTERM, shutdown_event.set)

    tasks = [asyncio.create_task(service())]
    await shutdown_event.wait()
    for task in tasks:
        task.cancel()
        try:
            await task
        except asyncio.CancelledError:
            pass

asyncio.run(main())