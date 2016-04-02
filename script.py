__name__ = "vutsuak"

from telegram import Updater
import serial

updater = Updater(token='167231176:AAF78E1Zbybmuz4Bs-qygnYQtGHrAq8Ozis')

dispatcher = updater.dispatcher


def start(bot, update):
    bot.sendMessage(chat_id=update.message.chat_id, text="Wanna know room stats")


dispatcher.addTelegramCommandHandler('start', start)


def unknown(bot, update):
    bot.sendMessage(chat_id=update.message.chat_id, text="No such command")


dispatcher.addUnknownTelegramCommandHandler(unknown)


def temp(bot, update, args):
    temp = 0
    ct = 0
    ser = serial.Serial('COM7', 9600)
    while ct != 5:
        temp = (ser.readline())
        print temp
        ct += 1
    bot.sendMessage(chat_id=update.message.chat_id, text=temp + " Centigrade")


dispatcher.addTelegramCommandHandler('temp', temp)


def humidity(bot, update, args):
    humnidity = 0
    ct = 0
    ser = serial.Serial('COM7', 9600)
    while ct != 5:
        humidity = (ser.readline())
        print humnidity
        ct += 1
    bot.sendMessage(chat_id=update.message.chat_id, text=humidity + "%")


dispatcher.addTelegramCommandHandler('humidity', humidity)


def ldr(bot, update, args):
    ldr = 0
    ct = 0
    ser = serial.Serial('COM7', 9600)
    while ct != 5:
        ldr = (ser.readline())
        print ldr
        ct += 1
    bot.sendMessage(chat_id=update.message.chat_id, text=ldr)


dispatcher.addTelegramCommandHandler('ldr', ldr)


def lamp(bot, update, args):
    lamp = "lamp is on !!!!"
    ser = serial.Serial('COM7', 9600)

    bot.sendMessage(chat_id=update.message.chat_id, text=lamp)


dispatcher.addTelegramCommandHandler('lamp', lamp)

updater.start_polling()
