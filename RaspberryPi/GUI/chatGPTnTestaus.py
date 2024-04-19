from tkinter import *
import arduino_communication
import threading
import time
from tkinter import ttk

max_count = 6
count = 0
light_show_bool = 0
last_count = -1

# Funktio, joka päivittää taulukon
def update_table():
    global count, last_count
    while True:
        # Lisää uusi rivi taulukkoon
        if count != last_count:
            current_time = time.strftime("%H:%M:%S")
            table.insert('', 'end', values=(count, current_time))
            last_count = count
        time.sleep(5)

# Päivitä ihmisten määrä GUI:ssa
def update_people_count():
    while True:
        global count
        count = int(arduino_communication.read_from_arduino())
        if count==max_count:
            people_inside_textlabel.config(fg="red", text="Sali on täynnä! Ihmisiä on sisällä jo " + str(count) + "/" + str(max_count)) 
        else:
            people_inside_textlabel.config(fg="black", text="Ihmisiä sisällä yhteensä: " + str(count) + "/" + str(max_count))

def close():
    arduino_communication.close_serial()
    win.destroy()

def change_lightshow():
    global light_show_bool
    light_show_bool = 1 - light_show_bool
    arduino_communication.write_to_arduino(str(light_show_bool) + "\n")

win = Tk()
win.title("People Counter")
myFont = ("Helvetica", 20, "bold")

frame = Frame(win)
frame.pack(padx=500, pady=120)

people_inside_textlabel = Label(frame, text="Ihmisiä sisällä yhteensä: 0/" + str(max_count), font=myFont)
people_inside_textlabel.grid(row=0, column=0)

newline_text = Label(frame, text="\n")
newline_text.grid(row=1, columnspan=1)

valomerkki_Button = Button(frame, text='Valomerkki', font=myFont, command=change_lightshow, bg="lightblue")
valomerkki_Button.grid(row=2, column=0, pady=(0,20))

exitButton = Button(frame, text='Lopeta', font=myFont, command=close, height=1, width=6)
exitButton.grid(row=3, column=0, pady=(20,0))

# Luo taulukko
table_frame = Frame(win)
table_frame.pack(pady=20)
table_headers = ['Määrä', 'Aika']
table = ttk.Treeview(table_frame, columns=table_headers, show='headings')
table.grid(row=0, column=0, sticky='nsew')
for header in table_headers:
    table.heading(header, text=header)
table_scroll = Scrollbar(table_frame, orient='vertical', command=table.yview)
table_scroll.grid(row=0, column=1, sticky='ns')
table.configure(yscrollcommand=table_scroll.set)

# Käynnistä ihmisten määrän päivitys ja taulukon päivitys
serial_thread = threading.Thread(target=update_people_count)
serial_thread.start()
table_update_thread = threading.Thread(target=update_table)
table_update_thread.start()

win.mainloop()
