#include "anzeigeWeb.h"

int AnzeigeWeb::bild2html(Bild* bild) {
	for (unsigned char bitwahl = 1; bitwahl; bitwahl <<= 2) {
		for (int idy = 0; idy < (int)(bild->bildHoehe / bild->anzahlPanel); idy++) {
			cout << "<tr>";
			for (int idx = 0; idx < bild->bildBreite; idx++) {
				cout << "<td class='x" << idx << " y" << idy << "' style='background: rgb(" << 255 * (bool)(bild->bildPixel[idy][idx] & (bitwahl << 1)) << "," << 255 * (bool)(bild->bildPixel[idy][idx] & bitwahl) << ",0);'></td>" << endl;
			}
			cout << "</tr>"<<endl;
		}
	}
	cout << "<tr></tr>" << endl;
	return 1;
}
AnzeigeWeb::AnzeigeWeb() {

}