from tkinter import *
import arduino_communication
import threading

count = 0
light_show_bool = 0 
  
# Päivitä ihmisten määrä GUI:ssa
def update_people_count():
    while True:
        global count
        count = int(arduino_communication.read_from_arduino())
        if count==10:
            people_inside_textlabel.config(fg="red", text="Sali on täynnä!")
        else:
            people_inside_textlabel.config(fg="black", text="Ihmisiä sisällä yhteensä: " + str(count))
            
        arduino_communication.write_to_arduino(light_show_bool)
        
def close():
    arduino_communication.close_serial()
    win.destroy()
    
def change_lightshow():
    global light_show_bool
    if light_show_bool == 1:
        light_show_bool = 0
    else:
        light_show_bool = 1
        
     

win = Tk()
win.title("People Counter")
myFont = ("Helvetica", 12, "bold")

frame = Frame(win)
frame.pack(padx=500, pady=400)

people_inside_textlabel = Label(frame, text="Ihmisiä sisällä yhteensä: 0", font=myFont)
people_inside_textlabel.grid(row=0, column=0)

people_inside_countlabel = Label(frame, text="0", font=myFont)
#people_inside_countlabel.grid(row=0, column=1)

newline_text = Label(frame, text="\n")
newline_text.grid(row=1, columnspan=1)

valomerkki_Button = Button(frame, text='Valomerkki', font=myFont, command=change_lightshow, bg="lightblue")
valomerkki_Button.grid(row=2, column=0, pady=(0,20))


exitButton = Button(frame, text='Lopeta', font=myFont, command=close, height=1, width=6)
exitButton.grid(row=3, column=0, pady=(20,0))



# Käynnistä ihmisten määrän päivitys
serial_thread = threading.Thread(target=update_people_count)
serial_thread.start()

win.mainloop()