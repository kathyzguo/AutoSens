import socket
import cv2

def predict(frame, sensors):
    return "TODO"

if __name__ == "__main__":
    srv = socket.socket()
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind(("0.0.0.0", 5000))
    srv.listen(1)

    while True:
        conn, addr = srv.accept()
        print("ESP32 connected:", addr)
        f = conn.makefile("rw", encoding = "utf-8", newline = "\n")
        try:
            while True:
                line = f.readline()
                cap = cv2.VideoCapture(0)
                ok, frame = cap.read()
                if not line:
                    break
                result = predict(frame, line.strip())
                f.write(result + "\n")
                f.flush()
        finally:
            conn.close()