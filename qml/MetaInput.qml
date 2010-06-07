import Qt 4.6

Rectangle {
    width: 640
    height: 480


    Rectangle {
        id: rectangle1
        x: 311
        y: 222
        width: 109
        height: 26
        color: "#ffffff"
        radius: 9
        clip: false
        visible: true
        border.color: "#ffffff"
        border.width: 3

        TextInput {
            id: textinput1
            x: 9
            y: 3
            width: 92
            height: 20
            text: "textInput"
        }
    }

    }
