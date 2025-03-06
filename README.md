# GUBER

## Classes
### Bookings
Required headers:
- #include <<huh>QString>
- #include <<huh>QVector2D>
- #include <<huh>QDateTime>
- #include <<huh>QDataStream>
- #include <<huh>QSqlQuery>

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

        class IDatabaseEntry {
            + GetInsertQuery() QSqlQuery
        }

        PlaneBooking--|>Booking
        CarBooking--|>Booking
        IDatabaseEntry <|.. PlaneBooking
        IDatabaseEntry <|.. CarBooking
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

### Database
Required headers:
- #include <<huh>QSql>
- #include <<huh>QSqlQuery>

```mermaid
    classDiagram
        class Database {
            + Database(filePath: const QString&)
            + ~Database()
            - database : QSqlDatabase
            + Query(query : const QString&) bool
            + Query(query : const QSqlQuery&) bool
        }
```