import subprocess
import time
import pandas as pd
import sqlite3
import os

# 파일 경로 설정
EXE_PATH = "C:/Users/user/Documents/python_db_connect/musagozip/x64/Debug/musagozip.exe"
CSV_PATH = "C:/Users/user/Documents/python_db_connect/musagozip/musagozip/sensor_result.csv"
DB_PATH = "C:/Users/user/Documents/python_db_connect/musagozip/db/log.db"

# 1. 센서 시뮬레이터 실행
print("🚀 센서 시뮬레이터 실행 중...")
subprocess.run([EXE_PATH], check=True)
time.sleep(1)  # 파일 저장 완료까지 잠깐 대기

# 2. CSV 파일 존재 여부 확인
if not os.path.exists(CSV_PATH):
    print("❗ sensor_result.csv 파일이 존재하지 않습니다.")
    exit()

# 3. CSV 데이터 읽기
df = pd.read_csv(CSV_PATH, encoding='cp949')  # 필요시 utf-8 또는 utf-8-sig 로 바꿔도 됨

# 4. DB 연결 및 테이블 생성
os.makedirs(os.path.dirname(DB_PATH), exist_ok=True)
conn = sqlite3.connect(DB_PATH)
cursor = conn.cursor()

cursor.execute('''
    CREATE TABLE IF NOT EXISTS sensor_data (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        timestamp TEXT,
        temperature REAL,
        gas REAL,
        power REAL,
        sound REAL,
        risk TEXT
    )
''')

# ✅ 기존 데이터 삭제 (항상 최신 CSV 기준으로 덮어쓰기)
cursor.execute("DELETE FROM sensor_data")
conn.commit()

# 5. 데이터 삽입
for _, row in df.iterrows():
    cursor.execute('''
        INSERT INTO sensor_data (timestamp, temperature, gas, power, sound, risk)
        VALUES (?, ?, ?, ?, ?, ?)
    ''', (
        row['timestamp'], row['temperature'], row['gas'],
        row['power'], row['sound'], row['risk']
    ))

conn.commit()
conn.close()

print("✅ 최신 CSV 데이터가 DB에 새로 저장되었습니다.")
