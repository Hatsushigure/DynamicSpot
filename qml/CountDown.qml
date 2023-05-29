import QtQuick
import DynamicSpot

Rectangle {
	property color textColor
	property alias shortText: base.shortText
	property alias fullText: base.fullText

	CountDownBase {id: base}

	id: root
	width: implicitWidth; height: implicitHeight
	implicitWidth: container.width + radius; implicitHeight: container.height + radius
	border.width: 0
	color: "#80000000"
	state: base.stateString
	states: [
		State {
			name: "showShort"

			PropertyChanges {target: container; width: Math.max(shortLabel.implicitWidth, shortLabel.implicitHeight); height: width}
			PropertyChanges {target: root; radius: Math.max(container.height, container.width)}
		},
		State {
			name: "showFull"

			PropertyChanges {target: fullLabel; opacity: 1}
			PropertyChanges {target: shortLabel; opacity: 0}
			PropertyChanges {target: container; width: fullLabel.implicitWidth; height: fullLabel.implicitHeight}
			PropertyChanges {target: root; radius: 12}
		}
	]
	transitions: [
		Transition {
			from: "showShort"; to: "showFull"

			SequentialAnimation {
				NumberAnimation {target: shortLabel; duration: 250; property: "opacity"}
				NumberAnimation {target: root; duration: 500; property: "radius"; easing.type: Easing.InExpo}
				NumberAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 750; properties: "width, height"}
				NumberAnimation {target: fullLabel; duration: 250; property: "opacity"}
			}
		},
		Transition {
			from: "showFull"; to: "showShort"

			SequentialAnimation {
				NumberAnimation {target: fullLabel; duration: 250; property: "opacity"}
				NumberAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.InExpo; duration: 750; properties: "width, height"}
				NumberAnimation {target: root; duration: 500; property: "radius"; easing.type: Easing.OutExpo}
				NumberAnimation {target: shortLabel; duration: 250; property: "opacity"}
			}
		}
	]

	Item {
		id: container
		anchors.centerIn: parent

		Text {
			id: shortLabel
			anchors.centerIn: container
			color: root.textColor
			textFormat: Text.MarkdownText
			text: base.shortText
			font.pointSize: 24
		}
		Text {
			id: fullLabel
			opacity: 0
			anchors.centerIn: container
			color: root.textColor
			textFormat: Text.MarkdownText
			text: base.fullText
			font.pointSize: 24
		}
	}
}
