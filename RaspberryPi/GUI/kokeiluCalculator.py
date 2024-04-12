from tkinter import *
import arduino_communication


def close():
    arduino_communication.close_serial()
    win.destroy()

win = Tk()
win.title("People Counter")
myFont = ("Helvetica", 12, "bold")

frame = Frame(win)
frame.pack(padx=200, pady=180)

people_inside_textlabel = Label(frame, text="Ihmisiä sisällä yhteensä: 0", font=myFont, fg="red")
people_inside_textlabel.grid(row=0, column=0)

people_inside_countlabel = Label(frame, text="0", font=myFont)
#people_inside_countlabel.grid(row=0, column=1)

newline_text = Label(frame, text="\n")
newline_text.grid(row=1, columnspan=1)

exitButton = Button(frame, text='Lopeta', font=myFont, command=close, height=1, width=6)
exitButton.grid(row=2, column=1)

# Päivitä ihmisten määrä GUI:ssa
def update_people_count():
    count = int(arduino_communication.read_from_arduino())
    if count < 0:
        count = 0
    elif count > 10:
        count = 10
        people_inside_textlabel.config(fg="red", text="Ihmisiä sisällä yhteensä: " + str(count) + " sali on täynnä")
    else:
        people_inside_textlabel.config(fg="black", text="Ihmisiä sisällä yhteensä: " + str(count))
    #people_inside_countlabel.config(text=count)
    win.after(1000, update_people_count)

# Käynnistä ihmisten määrän päivitys
update_people_count()

win.mainloop()
