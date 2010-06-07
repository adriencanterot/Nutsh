import Qt 4.6

Rectangle {
    width: 440
    height: 280
    color: "#000000"
    opacity: 0.7

    Rectangle {
        id: rectangle3
        x: 35
        y: 149
        width: 317
        height: 26
        color: "#000000"
        radius: 9
        clip: false
        border.color: "#ffffff"
        TextInput {
            id: textinput3
            x: 9
            y: 3
            width: 288
            height: 20
            color: "#ffffff"
            text: "textInput"
            selectionColor: "#ff8a4f"
            selectedTextColor: "#ff6200"
            horizontalAlignment: "AlignLeft"
        }
        visible: true
        border.width: 3
        opacity: 1
    }

    Rectangle {
            id: rectangle2
            x: 35
            y: 89
            width: 317
            height: 26
            color: "#000000"
            radius: 9
            clip: false
            border.color: "#ffffff"
            TextInput {
                id: textinput2
                x: 9
                y: 3
                width: 288
                height: 20
                color: "#ffffff"
                text: "textInput"
                selectionColor: "#ff8a4f"
                selectedTextColor: "#ff6200"
                horizontalAlignment: "AlignLeft"
            }
            visible: true
            border.width: 3
            opacity: 1
        }

Rectangle {
            id: rectangle1
            x: 35
            y: 32
            width: 317
            height: 26
            color: "#000000"
            radius: 9
            opacity: 1
            clip: false
            border.color: "#ffffff"
            visible: true
            border.width: 3

            TextInput {
                id: textinput1
                x: 9
                y: 3
                width: 288
                height: 20
                color: "#ffffff"
                text: "textInput"
                horizontalAlignment: "AlignLeft"
                selectedTextColor: "#ff6200"
                selectionColor: "#ff8a4f"
            }
        }


Rectangle {
    id: rectangle4
    x: 277
    y: 213
    width: 78
    height: 21
    color: "#000000"
    radius: 13
    clip: false
    border.color: "#ffffff"
    visible: true
    border.width: 3
    opacity: 1

    TextInput {
        id: textinput5
        x: 19
        y: 2
        width: 41
        height: 15
        color: "#ffffff"
        text: "Done"
        focusOnPress: false
        selectionColor: "#ffffff"
        readOnly: true
        selectedTextColor: "#ffffff"
    }
}


Rectangle {
    id: rectangle5
    x: 181
    y: 213
    width: 78
    height: 21
    color: "#000000"
    radius: 13
    clip: false
    border.color: "#ffffff"
    visible: true
    border.width: 3
    opacity: 1

    TextInput {
        id: textinput4
        x: 15
        y: 2
        width: 48
        height: 15
        color: "#ffffff"
        text: "Cancel"
        selectedTextColor: "#ffffff"
        selectionColor: "#ffffff"
        focusOnPress: false
        readOnly: true
    }
}


}
