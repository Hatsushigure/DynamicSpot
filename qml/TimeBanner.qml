import QtQuick
import DynamicSpot
import "." as App

Rectangle {
	property alias sloganText: sloganLabel.text
	property color textColor

	TimeBannerBase {
		id: base
		scheduleHost.onCurrentItemChanged: {
			timerShowSlogan.stop()
			timerShowTime.stop()
			timerShowSlogan.interval = scheduleHost.currentItem.durationSeconds * 1000
			timerShowSlogan.start()
			timerShowSchedule.start()
		}
	}

	id: root
	implicitWidth: container.width + radius; implicitHeight: container.height + radius
	radius: 12
	border.width: 0
	color: "#80000000"
	state: base.stateString
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
			text: base.timeText
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
			iconFileName: base.scheduleHost.currentItem.iconFileName
			titleText: base.scheduleHost.currentItem.title
			subtitleText: base.scheduleHost.currentItem.subtitle
		}
	}
	Timer {
		id: timerShowSchedule
		interval: 1
		onTriggered: {
			state = "showTime"
			state = "showSchedule"
		}
	}
}
