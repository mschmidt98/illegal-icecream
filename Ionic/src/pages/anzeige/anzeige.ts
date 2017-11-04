import {Component} from '@angular/core';
import {IonicPage} from 'ionic-angular';
import {AlertController} from "ionic-angular";

/**
 * Generated class for the AnzeigePage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */
let activeButton;
let btnA;
let btnB;
let btnC;
let btnD;

@IonicPage()
@Component({
    selector: 'page-anzeige',
    templateUrl: 'anzeige.html',
})
export class AnzeigePage {

    constructor(public alertCtrl: AlertController) {

        // Button-Objekte aus HTML ziehen
        const buttons = document.getElementsByTagName('button');
        for (let i = 0; i < buttons.length; i++) {
            let current = buttons[i];

            if (current.innerText == 'A') {
                btnA = current;
            }
            else if (current.innerText == 'B') {
                btnB = current;
            }
            else if (current.innerText == 'C') {
                btnC = current;
            }
            else if (current.innerText == 'ON/OFF') {
                btnD = current;
            }
        }
    }

    showRadio() {
        let alert = this.alertCtrl.create();
        alert.setTitle('Was stimmt?');

        alert.addInput({
            type: 'radio',
            label: 'Blaue LEDs',
            value: 'a'
        });

        alert.addInput({
            type: 'radio',
            label: 'Graue LEDs',
            value: 'b'
        });

        alert.addInput({
            type: 'radio',
            label: 'Helles Licht',
            value: 'c'
        });

        alert.addInput({
            type: 'radio',
            label: 'Alles',
            value: 'alle'
        });

        alert.addInput({
            type: 'radio',
            label: 'Keins',
            value: 'keine',
            checked: true
        });

        alert.addButton({
            text: 'Übernehmen',
            handler: data => {
                console.log(data);
            }
        });

        // noinspection JSIgnoredPromiseFromCall
        alert.present();
    }

    static ionViewDidLoad() {
        console.log('ionViewDidLoad AnzeigePage');
    }

    sendState(type) {
        // Alten aktiven auf Inaktiv setzten
        // Neu gedrückten auf activeButton setzen

        alert(btnA.classNames);
        if(activeButton != null)
        {
        }

        if (type == 'a') {
        }
        else if (type == 'b') {

        }
        else if (type == 'c') {

        }
        else {

        }

        AnzeigePage.httpGetAsync("http://192.168.178.36/light=" + type);
    }

    static httpGetAsync(theUrl) {
        const xmlHttp = new XMLHttpRequest();
        xmlHttp.open("GET", theUrl, true); // true for asynchronous
        xmlHttp.send(null);
    }
}
