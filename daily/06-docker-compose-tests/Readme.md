# Testing using docker-compose 
This small app shows how to prepare full cloud environment that can be used for testing whole services.

It contains: 
* ministack - MiniStack simulates AWS S3 on port 4566 (used to be LocalStack, most important thing to remember from training)
* database - PostgreSQL database
* db_fixture - preparing database before the tests
* s3_fixture - preparing buckets on simulated s3 env
* sut - application (the one inside app dir), that talks with db and s3
* trigger-sut - curl POST that triggers test
* verification-db - checking postconditions in database
* verification-s3 - checking postconditions in aws s3

