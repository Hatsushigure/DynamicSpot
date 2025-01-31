import QtQuick
import DynamicSpot as App

Item {
	signal clicked()

	id: root

	App.EasterEggMouseAreaBase {id: base}

	MouseArea {
		anchors.fill: parent

		onClicked: {
			base.click()
			if (!base.activated)
				return;
			root.clicked();
		}
	}
}
