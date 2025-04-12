# import mysql.connector
# from mysql.connector import Error

# def create_conn():
#     try:
#         conn = mysql.connector.connect(
#             host = "localhost",
#             user = "root",
#             password = "1234",
#             database = "test_db"
#         )
#         cursor = conn.cursor()
#         return conn, cursor
#     except Error as e:
#         print("DB 연결 오류",e)

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker,declarative_base
from dotenv import load_dotenv
import os

load_dotenv()
DB_HOST = os.getenv("DB_HOST")
DB_PORT = os.getenv("DB_PORT")
DB_USER = os.getenv("DB_USER")
DB_PASSWORD = os.getenv("DB_PASSWORD")
DB_NAME = os.getenv("DB_NAME")

DATABASE_URL = f"mysql+mysqlconnector://{DB_USER}:{DB_PASSWORD}@{DB_HOST}:{DB_PORT}/{DB_NAME}"
engine= create_engine(DATABASE_URL)
SessionLocal=sessionmaker(autocommit=False,autoflush=False,bind=engine)   

Base = declarative_base()
