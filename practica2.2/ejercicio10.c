/*

Si se borra algun enlace rigido se decrementara el numero de enlaces de su inodo, si este contador llega a cero el ya no quedara ningun
archivo asociado. Si se borra un enlace simbolico no le pasa nada al inodo al que apunta.
Si se borra el archivo original y no tiene ningun enlace rigido asociado, pues los enlaces simbolicos no funcionan pero siguen ahi.

*/