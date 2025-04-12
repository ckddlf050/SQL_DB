# from fastapi import FastAPI, HTTPException,Depends
# from db import engine,SessionLocal,Base
# from pydantic import BaseModel
# from models import User
# from sqlalchemy.orm import Session

# Base.metadata.create_all(bind=engine) #우리가 만든 모델이 db상에 존재하면 만들지 않고, 없다면 db상에 만들지 않고, 없다면 db상에 만들어 주겠다.

# app = FastAPI()

# def get_db():
#     db=SessionLocal()
#     try:
#         yield db
#     finally:
#         db.close()

# class UserCreate(BaseModel):
#     username: str
#     password: str
#     name: str
#     email: str
# class UserUpdate(BaseModel):
#     name: str
#     email: str
# @app.get("/") #CLIENT가 root 경로로 데이터 조회요청을 보냈다.
# def root():
#     return {"message" : "FastAPI 앱이 정상 작동중입니다."}
# # user 생성(CREATE)
# @app.post("/users")

# def create_user(user: UserCreate, db: Session = Depends(get_db)):
#     user_data = User(
#         username=user.username, 
#         password=user.password,
#         name=user.name,
#         email=user.email)
#     try:

#         db.add(user_data)
#         db.commit()
#         # conn, cursor = create_conn()
#         # sql = """
#         # INSERT INTO users (username, password, name, email)
#         # VALUES (%s, %s, %s, %s)
#         # """
#         # user_data = (user.username, user.password, user.name, user.email)
#         # cursor.execute(sql, user_data) #쿼리를 실행했지만 db상에 확정되는게 아니다. commit 해야함
#         # conn.commit()
#         return{"message":"사용자 등록이 완료되었습니다."}
#     except HTTPException as e:
#             raise HTTPException(status_code=400, detail=str(e))
#     # finally:
#     #     if conn.is_connected():
#     #         cursor.close()
#     #         conn.close()
# # user 조회(READ)
# @app.get("/users") 
# def get_users(db: Session = Depends(get_db)):
#     try:

#         result = db.query(User).all()
#         return result
#         # conn, cursor = create_conn()

#         # cursor.execute("SELECT * FROM users") #값을 가져오는 것 이므로 COMMIT 필요 없음.
#         # return cursor.fetchall() #fetchall:모든 결과를 다 받아 온다.

#     except HTTPException as e:
#             raise HTTPException(status_code=400, detail=str(e))
    
#     # finally:
#     #     if conn.is_connected():
#     #         cursor.close()
#     #         conn.close()
# # get_users()
# # create_user()
# # user 정보 업데이트(UPDATE)
# @app.put("/users/{username}") 
# def update_user(username: str, user: UserUpdate, db: Session = Depends(get_db)):
#     user_data = (user.name, user.email, username)
#     try:
#         db_user = db.query(User).filter(User.username == username).first()
#         db_user.name = user.name
#         db_user.email = user.email
#         db.commit()

#         # conn, cursor = create_conn()
        
#         # sql = "UPDATE users SET name = %s, email = %s WHERE username = %s"

#         # user_data = (user.name, user.email, username)
#         # cursor.execute(sql, user_data)
#         # conn.commit()
#         return {"message ":"사용자 정보 수정이 완료되었습니다."}

#     except HTTPException as e:
#             raise HTTPException(status_code=400, detail=str(e))
    
#     # finally:
#     #     if conn.is_connected():
#     #         cursor.close()
#     #         conn.close()

# # 유저 삭제(DELETE)
# @app.delete("/users/{username}")
# def delete_user(username: str, db: Session = Depends(get_db)):
#     try:
#         db_user = db.query(User).filter(User.username == username).first()
#         db.delete(db_user)
#         db.commit()
#         return {"message": "사용자 삭제가 완료되었습니다."}

#     except Exception as e:
#         raise HTTPException(status_code=400, detail=str(e))
    
# # # user 정보 삭제(DELETE)
# # @app.delete("/users/{username}") 
# # def delete_user(username:str):
# #     try:
# #         conn, cursor = create_conn()

# #         sql = "DELETE FROM users WHERE username = %s"
# #         cursor.execute(sql, (username,))
# #         conn.commit() #데이터를 수정 할 땐 commit이 필요하다.
# #         return {"message ":"사용자 정보 삭제 완료되었습니다."}
# #     except HTTPException as e:
# #             raise HTTPException(status_code=400, detail=str(e))
# #     finally:
# #         if conn.is_connected():
# #             cursor.close()
# #             conn.close()
# # update_user()
# # get_users()
# # delete_user()

from fastapi import FastAPI, HTTPException, Depends
from db import engine, SessionLocal, Base
from pydantic import BaseModel
from models import User
from sqlalchemy.orm import Session

Base.metadata.create_all(bind=engine)

app = FastAPI()


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


class UserCreate(BaseModel):
    username: str
    password: str
    name: str
    email: str


class UserUpdate(BaseModel):
    name: str
    email: str


@app.get("/")
def root():
    return {"message": "FastAPI 앱이 정상 작동중입니다."}


# 유저 생성(CREATE)
@app.post("/users")
def create_user(user: UserCreate, db: Session = Depends(get_db)):
    user_data = User(
        username=user.username, password=user.password, name=user.name, email=user.email
    )
    try:
        db.add(user_data)
        db.commit()
        return {"message": "사용자 등록이 완료되었습니다."}

    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))


# 유저조회(READ)
@app.get("/users")
def get_users(db: Session = Depends(get_db)):
    try:
        result = db.query(User).all()
        return result

    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))


# 유저 정보 업데이트(UPDATE)
@app.put("/users/{username}")
def update_user(username: str, user: UserUpdate, db: Session = Depends(get_db)):
    try:
        db_user = db.query(User).filter(User.username == username).first()
        db_user.name = user.name
        db_user.email = user.email
        db.commit()

        return {"message": "사용자 정보 수정이 완료되었습니다."}

    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))


# 유저 삭제(DELETE)
@app.delete("/users/{username}")
def delete_user(username: str, db: Session = Depends(get_db)):
    try:
        db_user = db.query(User).filter(User.username == username).first()
        db.delete(db_user)
        db.commit()
        return {"message": "사용자 삭제가 완료되었습니다."}

    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))