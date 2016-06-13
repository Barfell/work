//void TIM_Init(TIM_NumberTypeDef NumberTypeDef, TIM_SouceClkTypeDef SouceClkTypeDef, TIM_DivTypeDef DivTypeDef)
//{
//  if(NumberTypeDef == TIM_A)
//  {
//    switch(SouceClkTypeDef)
//    {
//     case TIM_SouceClk_ACLK: TACTL = TASSEL_1 + DivTypeDef;
//      break;
//     case TIM_SouceClk_SMCLK:TACTL = TASSEL_2 + DivTypeDef;
//      break;
//     case TIM_SouceClk_TACLK:TACTL = TASSEL_0 + DivTypeDef;
//      break;
//     case TIM_SouceClk_INCLK:TACTL = TASSEL_3 + DivTypeDef;
//      break;
//    }
//  }else if(NumberTypeDef == TIM_B)
//  {
//    switch(SouceClkTypeDef)
//    {
//     case TIM_SouceClk_ACLK: TBCTL = TBSSEL_1 + DivTypeDef;
//      break;
//     case TIM_SouceClk_SMCLK:TBCTL = TBSSEL_2 + DivTypeDef;
//      break;
//     case TIM_SouceClk_TACLK:TBCTL = TBSSEL_0 + DivTypeDef;
//      break;
//     case TIM_SouceClk_INCLK:TBCTL = TBSSEL_3 + DivTypeDef;
//      break;
//    }
//  }
//}
//void TIM_Mode
