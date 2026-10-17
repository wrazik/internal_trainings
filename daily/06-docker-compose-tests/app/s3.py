import boto3

session = boto3.client(
    "s3",
    endpoint_url="http://ministack:4566",
    region_name="us-east-1",
    aws_access_key_id="test",
    aws_secret_access_key="test",
)

BUCKET = "bucket"
