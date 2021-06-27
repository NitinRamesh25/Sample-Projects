import { Component } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})
export class AppComponent {
  public eventList: string[] = [];

  constructor(private http: HttpClient) {
    this.http.get<any>('http://localhost:8000/event').subscribe(
      (response) => {
        console.log(`got reponse: ${response}`);
        this.eventList = response;
      },
      (error) => console.log(`got error: ${error.message}`)
    );
  }
}
