FROM python:3.10-slim

RUN apt-get update && apt-get install ffmpeg libturbojpeg0 libgl1 libgphoto2-dev fonts-noto-color-emoji libexif12 libgphoto2-6 libgphoto2-port12 libltdl7 -y

WORKDIR /photobooth
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
RUN pip install --prefer-binary photobooth-app
EXPOSE 8000

WORKDIR /photobooth/data
ENTRYPOINT [ "photobooth" ]

