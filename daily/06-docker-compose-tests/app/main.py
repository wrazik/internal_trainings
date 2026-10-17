from fastapi import FastAPI
from .db import SessionLocal
from .models import Item
from .s3 import session as s3, BUCKET

app = FastAPI()

@app.post("/items")
def create_item(name: str):
    # save in postgres
    db = SessionLocal()
    item = Item(name=name)
    db.add(item)
    db.commit()
    db.refresh(item)


    response = s3.list_buckets()

    s3.put_object(
        Bucket=BUCKET,
        Key=f"item-{item.id}.txt",
        Body=f"Item stored: {item.name}"
    )

    return {"id": item.id, "name": item.name}


@app.get("/items/{item_id}")
def get_item(item_id: int):
    db = SessionLocal()
    item = db.query(Item).get(item_id)
    if not item:
        return {"error": "not found"}

    data = s3.get_object(
        Bucket=BUCKET,
        Key=f"item-{item.id}.txt"
    )["Body"].read().decode()

    return {
        "id": item.id,
        "name": item.name,
        "s3_data": data,
    }

