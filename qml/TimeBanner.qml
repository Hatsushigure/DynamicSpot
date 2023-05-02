import QtQuick
import DynamicSpot
import "." as App

Rectangle {
	property alias timeText: timeLabel.text
	property alias sloganText: sloganLabel.text
	property color textColor

	id: root
	implicitWidth: container.width + radius; implicitHeight: container.height + radius
	radius: 12
	border.width: 0
	color: "#80000000"
	state: "showTime"
	states: [
		State {name: "showTime"},
		State {
			name: "showSlogan"

			PropertyChanges {target: sloganLabel; opacity: 1}
			PropertyChanges {target: timeLabel; font.pointSize: 16}
			PropertyChanges {target: container; width: sloganLabel.implicitWidth; height: sloganLabel.implicitHeight + timeLabel.implicitHeight}
		},
		State {
			name: "showSchedule"

			PropertyChanges {target: scheduleViewer; visible: true}
			PropertyChanges {target: timeLabel; font.pointSize: 16}
			PropertyChanges {target: container; width: scheduleViewer.implicitWidth; height: scheduleViewer.implicitHeight + timeLabel.implicitHeight}
		}
	]
	transitions: [
		Transition {
			from: "showTime"; to: "showSlogan"

			SequentialAnimation {
				ParallelAnimation {
					NumberAnimation { target: timeLabel; property: "font.pointSize"; duration: 750; easing.type: Easing.OutExpo}
					PropertyAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 750; properties: "width, height"}
				}
				PropertyAnimation {target: sloganLabel; duration: 250; property: "opacity"}
			}
		},
		Transition {
			from: "showSlogan"; to: "showTime"

			SequentialAnimation {
				PropertyAnimation {target: sloganLabel; duration: 250; property: "opacity"}
				ParallelAnimation {
					PropertyAnimation {target: container; easing.overshoot: 1.5; easing.type: Easing.OutBack; duration: 750; properties: "width, height"}
					NumberAnimation { target: timeLabel; property: "font.pointSize"; duration: 750; easing.type: Easing.OutExpo}
				}
			}
		},
		Transition {
			from: "showTime"; to: "showSchedule"

			SequentialAnimation {
				PropertyAction {target: scheduleViewer; property: "x"; value: -scheduleViewer.width}
				PropertyAction {target: scheduleViewer; property: "visible"}
				ParallelAnimation {
					NumberAnimation {duration: 750; easing.type: Easing.OutCubic; target: container; properties: "width, height"}
					NumberAnimation {target: timeLabel; property: "font.pointSize"; duration: 750; easing.type: Easing.OutExpo}
				}
				NumberAnimation {target: scheduleViewer; to: 0; easing.overshoot: 1.5; easing.type: Easing.OutBack; property: "x"; duration: 500}
			}
		},
		Transition {
			from: "showSchedule"; to: "showTime"

			SequentialAnimation {
				NumberAnimation {target: scheduleViewer; property: "y"; to: -scheduleViewer.height; easing.overshoot: 1.1; duration: 500; easing.type: Easing.InBack}
				ParallelAnimation {
					NumberAnimation {target: container; duration: 750; easing.type: Easing.OutCubic; properties: "width, height"}
					NumberAnimation {target: timeLabel; property: "font.pointSize"; duration: 750; easing.type: Easing.OutExpo}
				}
				PropertyAction {target: scheduleViewer; property: "visible"}
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
			anchors.top: parent.top
			anchors.horizontalCenter: parent.horizontalCenter
			opacity: 0
			textFormat: Text.MarkdownText
			color: root.textColor
			text: "平凡者做完，优秀者做好，卓越者做到极致"
			font.pointSize: 24
		}

		App.ScheduleViewer {
			id: scheduleViewer
			visible: false
			x: 0; y:0
			textColor: root.textColor
			iconFileName: "qrc:/DynamicSpot/images/icons/colored/settings-256.svg"
			titleText: "Test item"
			subtitleText: "gggff--gfd$fgghyhbhuhvvfyujjghy"
		}
	}

	ScheduleHost {
		id: scheduleHost
		objectName: "scheduleHost"
		onCurrentItemChanged: {
			timerShowSlogan.stop()
			timerShowTime.stop()
			timerShowSlogan.interval = currentItem.durationSeconds * 1000
			timerShowSlogan.start()
			scheduleViewer.titleText = currentItem.title
			scheduleViewer.subtitleText = currentItem.subtitle
			scheduleViewer.iconFileName = currentItem.iconFileName
			timerShowSchedule.start()
		}
	}

	Timer {
		id: timerShowSlogan
		interval: 60 * 1000
		onTriggered: {
			root.state = "showTime"
			timerShowTime.interval = (Math.random() % 10 + 10) * 1000 * 60
			timerShowTime.start()
		}
	}

	Timer {
		id: timerShowSchedule
		interval: 0
		onTriggered: {
			state = "showTime"
			state = "showSchedule"
		}
	}

	Timer {
		id: timerShowTime
		interval: (Math.random() % 10 + 10) * 1000 * 60
		running: true
		onTriggered: {
			root.state = "showSlogan"
			timerShowSlogan.interval = 60 * 1000
			timerShowSlogan.start()
		}
	}

	Timer {
		id: changeTimeTimer
		triggeredOnStart: true
		interval: 500
		running: true
		repeat: true
		onTriggered: root.timeText = Qt.formatTime(new Date(), "HH:mm:ss")
	}
}
