<style>
@font-face {
  font-family: 'Uber';
  src: url('Fonts/UberMoveBold.otf') format('woff')
}
.custom-font {
  font-family: 'Uber', sans-serif;
}
</style>

<h1 class="custom-font">GUBER</h1>

## Classes
### Bookings
Required headers:
- #include <<huh>QString>
- #include <<huh>QVector2D>
- #include <<huh>QDateTime>
- #include <<huh>QDataStream>

```mermaid
    classDiagram
        class Booking {
            + Booking()
            - firstName : QString
            - lastName : QString
            - currentDate : QString
            - destinationAddress : QString
            - coordinates : QVector2D
            + GetFirstName() QString
            + GetLastName() QString
            + GetCurrentDate QDateTime
            + GetDestinationAddress() QString
            + GetCoordiantes() QVector2D
        }

        class CarBooking {
            + CarBooking()
            - cybertruck: bool
            + IsCybertruck() bool
        }

        class PlaneBooking {
            + PlaneBooking()
            - model: QString
            + GetModel() QString
        }

        PlaneBooking--|>Booking
        CarBooking--|>Booking
```
\
The above three classes will contain in and out operator for the QDataStream type.

```cpp
QDataStream& operator <<(QDataStream& stream, const CarBooking& booking);
QDataStream& operator >>(QDataStream& stream, CarBooking& booking);
```

### Network
Required headers:
- #include <<huh>QTcpServer>
- #include <<huh>QTcpSocket>
- #include <<huh>QList>
- #include <<huh>QByteArray>

```mermaid
    classDiagram
        class Server {
            + Server()
            + ~Server()
            - server : QTcpServer**
            - clients: QList<<huh>QTcpSocket*>
            + AddClient(socket : QTcpSocket*) void
            + RemoveClient(socket: QTcpSocket*) void
            + Start(port : qint16) bool
            + Stop() void

            + OnReceivedBytes(socket : QTcpSocket*) signal
        }

        class Client {
            + Client()
            + ~Client()
            - clientSocket : QTcpSocket**
            + Start(ip : QHostAddress, port : qint16) bool
            + Stop() void
            + Send(data : char*) qint64
        }
```