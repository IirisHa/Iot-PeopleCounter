#GUICalculator.py - Python3
from tkinter import *			

def close():
	RPi.GPIO.cleanup()
	win.destroy()

win=Tk()
win.title("People Counter")
myFont = ("Helvetica", 12, "bold")

frame = Frame(win)
frame.pack(padx=200, pady=180)

people_inside_textlabel = Label(frame, text="Ihmisiä sisällä: ", font=myFont)
people_inside_textlabel.grid(row=0, column=0)

people_inside_countlabel = Label(frame, text="0", font=myFont)
people_inside_countlabel.grid(row=0, column=1)

newline_text = Label(frame, text="\n")
newline_text.grid(row=1, columnspan=1  )

exitButton = Button(frame, text='Lopeta', font=myFont, command=close, height=1, width=6)
exitButton.grid(row=2, column=1)



win.mainloop()

