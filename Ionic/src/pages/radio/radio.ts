import { AlertController } from "ionic-angular";

export class RadioPage {

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
          value: 'd'
      });

      alert.addInput({
          type: 'radio',
          label: 'Keins',
          value: '',
          checked: true
      });

      alert.addButton('Abbrechen');
      alert.addButton({
          text: 'Ok',
          // handler: data => {
              // this.testRadioOpen = false;
              // this.testRadioResult = data;
          // }
      });

      alert.present();
  }
}
