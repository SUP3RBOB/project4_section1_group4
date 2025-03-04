# GUBER

### Classes
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
QDataStream& operator <<(QDataStream &stream, const CarBooking& booking);
QDataStream& operator >>(QDataStream &stream, CarBooking& booking);
```