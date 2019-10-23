//============================[COUNT_CHECK]========================
void countCheck() {
  if (oldCount != count) {
    changedCount = true;
    if (oldCount > count) {
      //if car in, send -1
      inOut = plusMinus[1];  //-
    }
    else if (oldCount < count) {
      //if car out, send +1
      inOut = plusMinus[0];  //+
    }
  }
  else {
    changedCount = false;
    //if not changed send =
    inOut = plusMinus[2];  //=
  }
  if (changedCount) {
    oldCount = count;
    changedCount = false;
    drawDisplay(count);
  }
}
