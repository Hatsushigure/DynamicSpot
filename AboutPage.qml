import QtQuick
import QtQuick.Controls.Material

Item {
	id: root

	Grid {
		rows: 1; columns: 2
		padding: 6; spacing: 4
		verticalItemAlignment: Grid.AlignVCenter

		Row {
			padding: 0; spacing: 4

			Image {
				source: "images/icons/avatar/avatar - 256.png"
				height: column1.height; width: height
			}

			Column {
				id: column1
				padding: 0; spacing: 0

				Text {text: "DynamicSpot"; font.pointSize: 20}
				Text {text: "v0.2.1"}
				Text {text: "MIT Lisence"}
				Text {text: "https://github.com/Hatsushigure/DynamicSpot"; color: "gray"}
			}
		}

		Row {
			padding: 0; spacing: 4

			Image {
				source: "images/icons/qt-logo-400.png"
				height: column2.height; width: height
			}

			Column {
				id: column2
				padding: 0; spacing: 0

				Text {text: "Qt"; font.pointSize: 18}
				Text {text: "6.5.0"; color: "gray"}
				Text {text: "https://qt.io"; color: "gray"}
			}
		}
	}
}
