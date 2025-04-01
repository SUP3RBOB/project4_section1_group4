import QtQuick
import QtLocation
import QtPositioning

Rectangle {
    id: window
    visible: true

    property Component comMarker: mapMarker
    property bool querying: false

    signal markerPositionChanged(location: string, latitude: double, longitude: double)

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(43.4788839,-80.5180008)
        zoomLevel: 14

        WheelHandler {
            id: wheel
            // workaround for QTBUG-87646 / QTBUG-112394 / QTBUG-112432:
            // Magic Mouse pretends to be a trackpad but doesn't work with PinchHandler
            // and we don't yet distinguish mice and trackpads on Wayland either
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                             ? PointerDevice.Mouse | PointerDevice.TouchPad
                             : PointerDevice.Mouse
            rotationScale: 1/30
            property: "zoomLevel"
        }
        DragHandler {
            id: drag
            target: map
            onTranslationChanged: (delta) => {
                map.pan(-delta.x, -delta.y)
            }
        }

        MouseArea {
            id: mouse

            anchors.fill: parent
            onClicked: {
                if (!querying) {
                    map.clearMapItems()
                    var pos = map.toCoordinate(Qt.point(mouse.x, mouse.y))
                    addMarker(pos.latitude, pos.longitude)
                    getCountry(pos)
                }
            }
        }
    }

    function addMarker(lat, lng) {
        var item = comMarker.createObject(window, {
            coordinate: QtPositioning.coordinate(lat, lng)
        })
        map.addMapItem(item)
    }

    Component {
        id: mapMarker
        MapQuickItem {
            id: markerImg
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position

            sourceItem: Image {
                id: image
                source: "http://maps.gstatic.com/mapfiles/ridefinder-images/mm_20_red.png"
            }
        }
    }

    GeocodeModel {
        id: geocodeModel;
        plugin: mapPlugin;
        autoUpdate: false;
        onLocationsChanged: {
            if (geocodeModel.count > 0) {
                var city = geocodeModel.get(0).address.city
                var country = geocodeModel.get(0).address.country
                var address = geocodeModel.get(0).address.text
                var latitude = geocodeModel.get(0).coordinate.latitude
                var longitude = geocodeModel.get(0).coordinate.longitude
                markerPositionChanged(address, latitude, longitude)
            }
            querying = false
        }
    }

    function getCountry(coordinate) {
        geocodeModel.query = coordinate
        geocodeModel.update()
        querying = true

    }
}
