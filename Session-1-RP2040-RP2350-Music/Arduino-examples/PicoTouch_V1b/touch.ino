void startTouch(){
   for (int i = 0; i < touch_count; i++) {
    touches[i].begin( touch_pins[i] );
  }
}

void checkTouch(){
  for ( int i = 0; i < touch_count; i++) {
    touches[i].update();
    if(touches[i].touched()){
      int touchval = touches[i].raw_value / 75;
      if (touchval > 127) touchval = 127;
      if (touchval!=lastAftertouch){
        if(aftEnable){
          note = i+transpose;
          channel = midiChannelA;
      if (note > split-transpose) channel = midiChannelB;
      MIDI.sendAfterTouch(touchval,channel);
      usbMIDI.sendAfterTouch(touchval,channel);
        }
        if(cctEnable){
      MIDI.sendControlChange(cctNo, touchval, channel);
      usbMIDI.sendControlChange(cctNo, touchval, channel);
        }
      lastAftertouch = touchval;
      delay(10);
      }
    }
    if ( touches[i].pressed() ) {
      touch_velocity[i]= touches[i].raw_value - touches[i].threshold;
      
      //if(debug){
      //Serial.print("Pin pressed ");
      //Serial.println( touches[i].pin );     
      //}
      
      note = i+transpose;
      channel = midiChannelA;
     

      if (note > split-transpose) {
        channel = midiChannelB;
        if(debug) {
          Serial.print("Split to channel ");
          Serial.println(channel);
        }
      }

      if(scale == 0 && noteEnable){
         if(debug) {
        Serial.print("Note On ");
        Serial.print(note);
        Serial.print(" on channel ");
        Serial.println(channel);
      }
      MIDI.sendNoteOn(note, touch_velocity[i], channel);
      usbMIDI.sendNoteOn(note, touch_velocity[i], channel);
      }
      if(scale == 1 && noteEnable) {
        if(debug) {
        Serial.print("Note On ");
        Serial.print(pentatonicTable[note]);
        Serial.print(" on channel ");
        Serial.println(channel);
        }
      MIDI.sendNoteOn(pentatonicTable[note], touch_velocity[i], channel);
      usbMIDI.sendNoteOn(pentatonicTable[note], touch_velocity[i], channel);
      }
      digitalWrite(LED_BUILTIN, HIGH);
    }

    if ( touches[i].released() ) {
      //if(debug){
      //Serial.print("Pin release ");
      //Serial.println( touches[i].pin );
      //}

      note = i+transpose;
      channel = midiChannelA;
      if (note > split-transpose) channel = midiChannelB;

      if(scale == 0 && noteEnable){
         if(debug) {
        Serial.print("Note Off ");
        Serial.print(note);
        Serial.print(" on channel ");
        Serial.println(channel);
      }
      MIDI.sendNoteOff(note, 0, channel);
      usbMIDI.sendNoteOff(note, 0, channel);
      }
      if(scale == 1 && noteEnable){
        if(debug) {
        Serial.print("Note Off ");
        Serial.print(pentatonicTable[note]);
        Serial.print(" on channel ");
        Serial.println(channel);
        }
      MIDI.sendNoteOff(pentatonicTable[note], 0, channel);
      usbMIDI.sendNoteOff(pentatonicTable[note], 0, channel);
      }
      digitalWrite(LED_BUILTIN, LOW);
    }

  }
}

void doCalibrate(){
  for (int i = 0; i < touch_count; i++) {
            digitalWrite(LED_BUILTIN, HIGH);
            touches[i].recalibrate();
            touch_threshold[i] = touches[i].threshold;
            if(debug)Serial.println(touch_threshold[i]);
          }
          if(debug)Serial.println("Calibrated");
          delay(1000);
          digitalWrite(LED_BUILTIN, LOW);
}
