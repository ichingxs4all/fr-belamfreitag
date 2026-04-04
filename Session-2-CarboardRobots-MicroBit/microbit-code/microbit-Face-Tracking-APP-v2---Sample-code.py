def on_bluetooth_connected():
    basic.show_icon(IconNames.HAPPY)
bluetooth.on_bluetooth_connected(on_bluetooth_connected)

def on_bluetooth_disconnected():
    basic.show_icon(IconNames.NO)
bluetooth.on_bluetooth_disconnected(on_bluetooth_disconnected)

def on_uart_data_received():
    global receivedString, x, y, z, yaw, pitch, mouth, left_eye, right_eye, roll, smile, face_visible
    receivedString = bluetooth.uart_read_until(serial.delimiters(Delimiters.NEW_LINE))
    x = parse_float(receivedString.substr(0, 2))
    y = parse_float(receivedString.substr(2, 2))
    z = parse_float(receivedString.substr(4, 2))
    yaw = parse_float(receivedString.substr(6, 2))
    pitch = parse_float(receivedString.substr(8, 2))
    mouth = parse_float(receivedString.substr(10, 2))
    left_eye = parse_float(receivedString.substr(12, 2))
    right_eye = parse_float(receivedString.substr(14, 2))
    roll = parse_float(receivedString.substr(16, 1))
    smile = parse_float(receivedString.substr(17, 1))
    face_visible = parse_float(receivedString.substr(18, 1))
    led.plot_bar_graph(yaw, 100)
    if face_visible:
        motor.servo(motor.Servos.S1, Math.map(mouth, 0, 100, 10, 90))
        motor.servo(motor.Servos.S8, Math.map(yaw, 0, 100, 0, 180))
bluetooth.on_uart_data_received(serial.delimiters(Delimiters.NEW_LINE),
    on_uart_data_received)

face_visible = 0
smile = 0
roll = 0
right_eye = 0
left_eye = 0
mouth = 0
pitch = 0
yaw = 0
z = 0
y = 0
x = 0
receivedString = ""
bluetooth.start_uart_service()
basic.show_icon(IconNames.SQUARE)