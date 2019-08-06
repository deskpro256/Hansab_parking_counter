//============================[COUNT_CHECK]========================
void countCheck() {
  if (oldCount != count) {
    changedCount = true;
    if (oldCount > count) {
      //if car in, send -1
      inOut = plusMinus[1];  //-
    }
    else {
      //if car out, send +1
      inOut = plusMinus[0];  //+
    }
  }
  else {
    changedCount = false;
  }
}
