import smtplib
from email.message import EmailMessage
import sys

if (len(sys.argv) > 1):
    recipient = sys.argv[1]
    # 1. Setup your credentials
    EMAIL_ADDRESS = "de.onschuldige.photobooth@gmail.com"
    EMAIL_PASSWORD = "tntn vxgr gyjo asiv" # Use an App Password, not your login password

    # 2. Create the email container
    msg = EmailMessage()
    msg['Subject'] = "Your photo from the Photobooth!"
    msg['From'] = EMAIL_ADDRESS
    msg['To'] = recipient
    msg.set_content("Your Original images got a bit changed in transit.")

    photo_path = "../media/ai_edited"

    list_of_files = glob.glob(f'{photo_path}/*') # * means all if need specific format then *.csv
    latest_file = max(list_of_files, key=os.path.getctime)

    try:
        with open(latest_file, 'rb') as f:
            file_data = f.read()
            file_name = f.name

        msg.add_attachment(file_data, maintype='image', subtype='png', filename=file_name)

    # 3. Send the email
    try:
        with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp:
            smtp.login(EMAIL_ADDRESS, EMAIL_PASSWORD)
            smtp.send_message(msg)
        print("Email sent successfully!")
        sys.exit(0)
    except Exception as e:
        print(f"Error: {e}")