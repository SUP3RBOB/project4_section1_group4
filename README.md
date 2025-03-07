# GUBER

## Classes
### Bookings
Required headers:
- #include <<huh>QString>
- #include <<huh>QVector2D>
- #include <<huh>QDateTime>
- #include <<huh>QDataStream>
- #include <<huh>QSqlQuery>
- #include <<huh>QDataStream>

```mermaid
    classDiagram
        class Booking {
            + Booking()
            - currentDate : QString
            - destinationAddress : QString
            - coordinates : QVector2D
            + GetCurrentDate() QDateTime
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

```mermaid
    classDiagram
        class UserAccount {
            - firstName : QString
            - lastName : QString
            + UserAccount()
            - email : QString
            + GetFirstName() QString
            + GetLastName() QString
            + GetEmail() QString
        }
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
            + OnStateChanged(state : ServerState) signal
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
```mermaid
    classDiagram
        class Enum-PacketHeader {
            StateChange = 0,
            CarBooking = 1,
            PlaneBooking = 2,
            AccountCreation = 3
        }

        class Enum-ServerState {
            CarMode = 0,
            PlaneMode = 1
        }
```

### Database
Required headers:
- #include <<huh>QSql>
- #include <<huh>QSqlQuery>

```mermaid
    classDiagram
        class Database {
            + Database()
            + ~Database()
            - database : QSqlDatabase
            + Query(query : const QString&) void
            + Query(query : const QSqlQuery&) void
            + EmailExists() bool
            + AccountExists()bool
        }
```