import { Component } from '@angular/core';

import { HomePage } from '../home/home';
import {AnzeigePage } from "../anzeige/anzeige";

@Component({
  templateUrl: 'tabs.html'
})
export class TabsPage {

  tabHome = HomePage;
  tabAnzeige = AnzeigePage;

  constructor() {

  }
}
