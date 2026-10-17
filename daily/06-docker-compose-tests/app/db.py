from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

DB_URL = "postgresql://pguser:password@database:5432/test"

engine = create_engine(DB_URL)
SessionLocal = sessionmaker(bind=engine)

