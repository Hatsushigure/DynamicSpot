import QtQuick
import DynamicSpot
import "." as App

Rectangle {
	property alias containerHeight: container.height
	property alias timeText: timeLabel.text
	property alias sloganText: sloganLabel.text
	property color textColor

	id: root
	width: container.width + radius
	radius: 12
	state: "showTime"
	states: [
		State {
			name: "showTime"
		},
		State {
			name: "showSlogan"

			PropertyChanges {target: sloganLabel; opacity: 1}
			PropertyChanges {target: timeLabel; opacity: 0}
			PropertyChanges {target: container; width: sloganLabel.implicitWidth; height: sloganLabel.implicitHeight}
		},
		State {
			name: "showSchedule"

			PropertyChanges {target: timeLabel; font.pointSize: 16}
			PropertyChanges {target: scheduleViewer; x: 0}
			PropertyChanges {target: container; width: scheduleViewer.implicitWidth; height: scheduleViewer.implicitHeight + timeLabel.implicitHeight}
		}
	]
	transitions: [
		Transition {
			from: "showTime"; to: "showSlogan"

			SequentialAnimation {
				PropertyAnimation {target: timeLabel; duration: 250; property: "opacity"}
				PropertyAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 750; properties: "width, height"}
				PropertyAnimation {target: sloganLabel; duration: 250; property: "opacity"}
			}
		},
		Transition {
			from: "showSlogan"; to: "showTime"

			SequentialAnimation {
				PropertyAnimation {target: sloganLabel; duration: 250; property: "opacity"}
				PropertyAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 750; properties: "width, height"}
				PropertyAnimation {target: timeLabel; duration: 250; property: "opacity"}
			}
		},
		Transition {
			from: "showTime"; to: "showSchedule"

			SequentialAnimation {
				ParallelAnimation {
					NumberAnimation {duration: 750; easing.type: Easing.OutCubic;target: container; properties: "width, height"}
					NumberAnimation {target: timeLabel; property: font.pointSize; duration: 750; easing.type: Easing.OutExpo}
				}
				XAnimator {target: scheduleViewer; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 500}
			}
		},
		Transition {
			from: "showSchedule"; to: "showTime"

			SequentialAnimation {
				YAnimator {target: scheduleViewer; to: -scheduleViewer.height; easing.overshoot: 1.1; duration: 500; easing.type: Easing.InBack}
				ParallelAnimation {
					NumberAnimation {target: container; duration: 750; easing.type: Easing.OutCubic; properties: "width, height"}
					NumberAnimation {target: timeLabel; property: font.pointSize; duration: 750; easing.type: Easing.OutExpo}
				}
				PropertyAction {target: scheduleViewer; properties: "y"; value: 0}
			}
		}

	]

	Item {
		id: container
		anchors.centerIn: root
		width: timeLabel.implicitWidth; height: timeLabel.implicitHeight
		clip: true

		Text {
			id: timeLabel
			anchors.horizontalCenter: container.horizontalCenter
			anchors.bottom: container.bottom
			opacity: 1
			textFormat: Text.MarkdownText
			color: root.textColor
			text: "00:00:00"
			font.pointSize: 24
		}

		Text {
			id: sloganLabel
			anchors.centerIn: container
			opacity: 0
			textFormat: Text.MarkdownText
			color: root.textColor
			text: "平凡者做完，优秀者做好，卓越者做到极致"
			font.pointSize: 24
		}

		App.ScheduleViewer {
			id: scheduleViewer
			x: -width; y: 0
			textColor: root.textColor
		}
	}

	ScheduleHost {
		id: scheduleHost
		objectName: "scheduleHost"
		onCurrentItemChanged: {
			showSloganTimer.stop()
			showSloganTimer.interval = currentItem.durationSeconds * 1000
			showSloganTimer.start()
			scheduleViewer.titleText = currentItem.title
			scheduleViewer.subtitleText = currentItem.subtitle
			scheduleViewer.iconFileName = currentItem.iconFileName
			state = "showTime"
			state = "showSchedule"
		}
	}

	Timer {
		id: changeTimeTimer
		interval: 500
		running: true
		repeat: true
		onTriggered: root.timeText = Qt.formatTime(new Date(), "HH:mm:ss")
	}

	Timer {
		id: showSloganTimer
		interval: 60 * 1000
		onTriggered: {
			root.state = "showTime"
			showTimeTimer.interval = (Math.random() % 10 + 10) * 1000 * 60
			showTimeTimer.start()
		}
	}

	Timer {
		id: showTimeTimer
		interval: (Math.random() % 10 + 10) * 1000 * 60
		running: true
		onTriggered: {
			root.state = "showSlogan"
			showSloganTimer.start()
		}
	}
}
