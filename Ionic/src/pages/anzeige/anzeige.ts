import {Component} from '@angular/core';
import {IonicPage} from 'ionic-angular';
import {AlertController} from "ionic-angular";

/**
 * Generated class for the AnzeigePage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

@IonicPage()
@Component({
    selector: 'page-anzeige',
    templateUrl: 'anzeige.html',
})
export class AnzeigePage {
    constructor(public alertCtrl: AlertController) {
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

        alert.present();
    }

    ionViewDidLoad() {
        console.log('ionViewDidLoad AnzeigePage');
    }

}
