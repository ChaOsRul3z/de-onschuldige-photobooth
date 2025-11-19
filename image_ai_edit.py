import glob
import os
from google import genai
from google.genai import types
from PIL import Image
from dotenv import load_dotenv

load_dotenv()

list_of_files = glob.glob(f'{os.getenv("MEDIA_PATH")}/*') # * means all if need specific format then *.csv
latest_file = max(list_of_files, key=os.path.getctime)



client = genai.Client(api_key=os.getenv("GEMINI_API_KEY"))

prompt = (
    "Put him in a purple shirt, sitting at a table in a restaurant."
)

image = Image.open(latest_file)

response = client.models.generate_content(
    model="gemini-2.5-flash-image",
    contents=[prompt, image],
)     

for part in response.parts:
    if part.text is not None:
        print(part.text)
    elif part.inline_data is not None:
        image = part.as_image()
        image.save("generated_image.png")
