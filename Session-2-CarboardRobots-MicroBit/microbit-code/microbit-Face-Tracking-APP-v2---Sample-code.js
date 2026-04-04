bluetooth.onBluetoothConnected(function () {
    basic.showIcon(IconNames.Happy)
})
bluetooth.onBluetoothDisconnected(function () {
    basic.showIcon(IconNames.No)
})
bluetooth.onUartDataReceived(serial.delimiters(Delimiters.NewLine), function () {
    receivedString = bluetooth.uartReadUntil(serial.delimiters(Delimiters.NewLine))
    x = parseFloat(receivedString.substr(0, 2))
    y = parseFloat(receivedString.substr(2, 2))
    z = parseFloat(receivedString.substr(4, 2))
    yaw = parseFloat(receivedString.substr(6, 2))
    pitch = parseFloat(receivedString.substr(8, 2))
    mouth = parseFloat(receivedString.substr(10, 2))
    left_eye = parseFloat(receivedString.substr(12, 2))
    right_eye = parseFloat(receivedString.substr(14, 2))
    roll = parseFloat(receivedString.substr(16, 1))
    smile = parseFloat(receivedString.substr(17, 1))
    face_visible = parseFloat(receivedString.substr(18, 1))
    led.plotBarGraph(
    yaw,
    100
    )
    if (face_visible) {
        motor.servo(motor.Servos.S1, Math.map(mouth, 0, 100, 10, 90))
        motor.servo(motor.Servos.S8, Math.map(yaw, 0, 100, 0, 180))
    }
})
let face_visible = 0
let smile = 0
let roll = 0
let right_eye = 0
let left_eye = 0
let mouth = 0
let pitch = 0
let yaw = 0
let z = 0
let y = 0
let x = 0
let receivedString = ""
bluetooth.startUartService()
basic.showIcon(IconNames.Square)
