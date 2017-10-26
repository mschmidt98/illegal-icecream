import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { AnzeigePage } from './anzeige';

@NgModule({
  declarations: [
    AnzeigePage,
  ],
  imports: [
    IonicPageModule.forChild(AnzeigePage),
  ],
})
export class AnzeigePageModule {}
