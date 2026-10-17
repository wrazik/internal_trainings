FROM python:3.14

WORKDIR /app
COPY . /app
RUN pip install -r requirements.txt

WORKDIR /
CMD uvicorn app.main:app --host 0.0.0.0 --port 8080
