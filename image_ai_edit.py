import glob
import os

path="/home/chaosrul3z/Workspaces/mct/de-onschuldige-photobooth/data/media/camera_original"

list_of_files = glob.glob(f'{path}/*') # * means all if need specific format then *.csv
latest_file = max(list_of_files, key=os.path.getctime)
print(latest_file)


# with open("/home/chaosrul3z/Workspaces/mct/de-onschuldige-photobooth/demofile.txt", "a") as f:
#   f.write("Now the file has more content!")

# from google import genai
# from google.genai import types
# from PIL import Image

# client = genai.Client(api_key="")

# prompt = (
#     "Create a picture of my cat eating a nano-banana in a "
#     "fancy restaurant under the Gemini constellation",
# )

# image = Image.open("data/media/camera_original/20251119-110501-169730.jpg")

# response = client.models.generate_content(
#     model="gemini-2.5-flash-image",
#     contents=[prompt, image],
# )

# for part in response.parts:
#     if part.text is not None:
#         print(part.text)
#     elif part.inline_data is not None:
#         image = part.as_image()
#         image.save("generated_image.png")
