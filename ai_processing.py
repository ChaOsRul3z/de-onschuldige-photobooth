import glob
import os
from dotenv import load_dotenv

from google import genai
from google.genai import types
from PIL import Image

load_dotenv()

list_of_files = glob.glob(f'{os.getenv("MEDIA_PATH")}/*') # * means all if need specific format then *.csv
latest_file = max(list_of_files, key=os.path.getctime)

audio_path = os.getenv("AUDIO_PATH")

image_modification_modifier = os.getenv("IMAGE_MODIFIER")
single_prompt_modifier = os.getenv("SINGLE_PROMPT_MODIFIER")

client = genai.Client(api_key=os.getenv("GEMINI_API_KEY"))



def transcribe_audio_file(file_path: str) -> str:
    # TESTING RETURN
    return format(os.getenv("TEMP_SPEECH_TO_TEXT"))

    myfile = client.files.upload(file=file_path)
    
    response = client.models.generate_content(
        model="gemini-2.5-flash", contents=["transcribe", myfile]
    )

    return response.text

def generate_single_prompt_from_text(text: str) -> str:
    return format(os.getenv("TEMP_SPEECH_TO_TEXT"))

    response = client.models.generate_content(
        model="gemini-2.5-flash", contents=[text + os.linesep + os.linesep + single_prompt_modifier]
    )

    return response.text

def modify_image_based_on_prompt(image_path: str, prompt: str):
    prompt = ( transcribe_audio_file(audio_path) + image_modification_modifier )
    image = Image.open(image_path)

    response = client.models.generate_content(
        model="gemini-2.5-flash-image",
        contents=[prompt, image],
    )     

    for part in response.parts:
        if part.text is not None:
            print(part.text)
        elif part.inline_data is not None:
            image = part.as_image()
            image.save(f"{os.getenv('AI_GEN_PATH')}/{os.path.basename(image_path)}_ai_gen.png")


# generate_single_prompt_from_text(transcribe_audio_file(audio_path))
modify_image_based_on_prompt(latest_file, generate_single_prompt_from_text(transcribe_audio_file(audio_path)))