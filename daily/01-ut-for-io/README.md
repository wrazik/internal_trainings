Mamy zadany kod:

```python
def process_file(path_in: str, path_out: str) -> None:
    with open(path_in, "r", encoding="utf-8") as f:
        content = f.read()

    modified = content.strip().upper()

    with open(path_out, "w", encoding="utf-8") as f:
        f.write(modified)
```

Chcąc napisać test integracyjny do tego, możemy użyć fixturę zawierającą tempdir:

```python
from main import process_file
from pytest import fixture
from tempfile import TemporaryDirectory
from pathlib import Path

@fixture
def create_env():
    with TemporaryDirectory() as d:
        dir_path = Path(d)
        input_file = dir_path / "input.txt"
        input_file.write_text("test\nstring")

        yield dir_path, input_file

def test_processing_file(create_env):
    dir, input = create_env
    output = dir / "output.txt"

    process_file(str(input), str(output))

    assert output.read_text().splitlines() == ["TEST", "STRING"]

```

Jeśli chcemy napisać test unitowy, możemy wykorzystać do tego unittest.mock:
```python
from main import process_file
from unittest.mock import mock_open, call, patch

@patch("builtins.open", new_callable=mock_open, read_data="data")
def test_process_file_with_mock(mock_file):
    process_file("some_file_in", "some_file_out")
    mock_file.assert_any_call("some_file_in", "r", encoding="utf-8")
    mock_file.assert_any_call("some_file_out", "w", encoding="utf-8")
    mock_file().write.assert_called_once_with("DATA")
```

Takie rozwiązanie ma sporo wad: testy są ściśle związane z implementacją: przy dużych zmianach w kodzie, konieczne jest przepisanie testów. 

Lepszym rozwiązaniem jest wydzielenie logiki biznesowej do osobnej funkcji i testowanie jej w izolacji:
```python
def process_content(file_content):
    return file_content.strip().upper()

def process_file(path_in: str, path_out: str) -> None:
    with open(path_in, "r", encoding="utf-8") as f:
        content = f.read()

    modified = process_content(content)

    with open(path_out, "w", encoding="utf-8") as f:
        f.write(modified)
```

```python
from main import process_content

def test_process_file():
    assert process_content("some_string") == "SOME_STRING"
```

Mocków powinniśmy używać do testów modułowych lub integracyjnych, w których nie ma możliwości odwzorowania prawdziwego środowiska. 
