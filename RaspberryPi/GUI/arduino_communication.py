import serial

# Alusta sarjayhteysportti
ser = serial.Serial('/dev/ttyUSB0', 9600) # Tarkista porttinumero ja baudinopeus

# Lue ihmisten määrä Arduinolta
def read_from_arduino():
    data = ser.readline()# Lue sarjatiedot ja poista ylimääräiset välilyönnit
    return int(data)
    
#Valomerkki-koodi    
def write_to_arduino(number):
    ser.write(number.encode())

# Sulje sarjayhteysportti
def close_serial():
    ser.close()


