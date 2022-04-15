size_t typeSMS,length =  strlen(smsTemp) - 1 - type_de_SMS(smsTemp);
                    if (type_de_SMS(smsTemp) != 0) {
                        typeSMS = 67;
                        // printf("\nSMS speciale");
                    } else {
                        typeSMS = 153;
                        // printf("\nSMS standard");
                    }
                    //Nombre de SMS
                    double fractpart,intpart,c;
                    if (type_de_SMS(smsTemp) != 0){
                        if (length <= 70) {
                            c = 1;
                        } else {
                            fractpart = modf(length / 67, &intpart);
                            c = intpart + (1 - fractpart);
                        }
                    } else {
                        if (length <= 160) {
                            c = 1;
                        } else {
                            fractpart = modf(length / 153, &intpart);
                            c = intpart + (1 - fractpart) ;
                        }
                    }
                    printf("\nTESTTT c = %f",c);
                    if (c == 1) {
                        if (typeSMS == 67) {
                            typeSMS = 70;
                        } else {
                            typeSMS = 160;
                        }
                    }
                    c = (int)(c);