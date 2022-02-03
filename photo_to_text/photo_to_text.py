import pytesseract 
import cv2
import asyncio
import aiogram
import pymysql
import datetime
import config as cnf
from aiogram.dispatcher import Dispatcher
from aiogram import types
from aiogram.utils.exceptions import (MessageToEditNotFound, MessageCantBeEdited, MessageCantBeDeleted,MessageToDeleteNotFound)
from aiogram.dispatcher import FSMContext
from aiogram.contrib.fsm_storage.memory import MemoryStorage
from aiogram.contrib.middlewares.logging import LoggingMiddleware
from aiogram import Bot
from aiogram.utils import executor
from aiogram.utils.markdown import text
import main as main


storage = MemoryStorage()
bot = Bot(token=cnf.TOKEN)

dp = Dispatcher(bot, storage=storage)
dp.middleware.setup(LoggingMiddleware())
gif = "https://i.gifer.com/U1RP.gif"
#"https://i.gifer.com/78ff.gif"
#"https://i.gifer.com/WS2c.gif"
#"https://i.gifer.com/ZWdx.gif"
#"https://i.gifer.com/Cwgf.gif"
#"C:\\Users\\Suren\\source\\repos\\photo_to_text\\XVo6.gif"

@dp.message_handler(commands=['start'])
async def process_callback_start(message: types.Message):

    await bot.send_message(message.from_user.id,f"Send me a photo")    

@dp.message_handler(content_types=['photo'])
async def handle_docs_photo(message_photo):
    msg = await bot.send_animation(message_photo.from_user.id,gif)
    msg_id = msg.message_id
    await message_photo.photo[-1].download('photo.jpg')
    data = await main.pht()
    await bot.delete_message(message_photo.from_user.id,msg_id)
    await bot.send_message(message_photo.from_user.id,f"TEXT>>>\n\n\n{data}")    

if __name__ == '__main__':	

    executor.start_polling(dp,timeout=None,fast=True,skip_updates=True)



