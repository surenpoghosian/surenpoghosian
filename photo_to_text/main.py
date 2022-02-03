import pytesseract 
import cv2
import asyncio



pytesseract.pytesseract.tesseract_cmd = 'C:\\Program Files\\Tesseract-OCR\\tesseract.exe'

async def pht():

	try:
		
		n_str=1640
		img =cv2.imread(f"C:\\Users\\Suren\\source\\repos\\bot\\{n_str}.png")
		img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
		config = r'--oem 3 --psm 6 -l eng+hye'
		data=pytesseract.image_to_string(img, config=config,lang= 'rus')
		print (data)
		return data	

	except Exception as ex:
		print(ex)
	

