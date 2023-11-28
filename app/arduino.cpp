#include "arduino.h"

Arduino::Arduino() {
    serial = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "COM5"; // Change this to your specific COM port
    serial->setPortName(arduino_port_name);
    serial->setBaudRate(QSerialPort::Baud9600); // Modify baud rate as needed
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
}

int Arduino::connect_arduino() {
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id &&
           serialPortInfo.productIdentifier() == arduino_uno_producy_id) {
            serial->setPort(serialPortInfo);
            if(serial->open(QSerialPort::ReadWrite)) {
                arduino_is_available = true;
                arduino_port_name = serialPortInfo.portName();
                qDebug() << "Connected to Arduino on port" << arduino_port_name;
                return 0; // Success
            }
        }
    }
    qDebug() << "Couldn't find Arduino!";
    return -1; // Failed to connect
}

int Arduino::close_arduino() {
    if(serial->isOpen()) {
        serial->close();
        qDebug() << "Arduino connection closed";
        return 0; // Success
    }
    qDebug() << "No Arduino connection to close";
    return -1; // No connection to close
}

int Arduino::write_to_arduino(const QString& message) {
    if (serial->open(QIODevice::ReadWrite)) {
        // Attempt to write data here
    } else {
        qDebug() << "Error opening serial port: " << serial->errorString();
    }if (serial->write("") == -1) {
        qDebug() << "Failed to write to serial port. Error: " << serial->errorString();
    } else {
        qDebug() << "Data written successfully to serial port";
    }
    if(serial->isWritable()) {
        serial->write(message.toUtf8());
        qDebug() << "Data sent to Arduino: " << message;
        return 0; // Success
    }

    qDebug() << "Couldn't write to serial!";
    return -1; // Failed to write
}

QByteArray Arduino::read_from_arduino() {
    if(serial->isReadable()) {
        data = serial->readAll();
        qDebug() << "Data received from Arduino: " << data;
        return data;
    }
    qDebug() << "Couldn't read from serial!";
    return QByteArray();
}

QSerialPort* Arduino::getserial() {
    return serial;
}

QString Arduino::getarduino_port_name() {
    return arduino_port_name;
}
