/**
 *  file    ConsoleShell.c
 *  date    2009/01/31
 *  author  kkamagui 
 *          Copyright(c)2008 All rights reserved by kkamagui
 *  brief   �ܼ� �п� ���õ� �ҽ� ����
 */

#include "ConsoleShell.h"
#include "Console.h"
#include "Keyboard.h"
#include "Utility.h"

// Ŀ�ǵ� ���̺� ����
SHELLCOMMANDENTRY gs_vstCommandTable[] =
{
        { "help", "Show Help", kHelp },
        { "cls", "Clear Screen", kCls },
        { "totalram", "Show Total RAM Size", kShowTotalRAMSize },
        { "strtod", "String To Decial/Hex Convert", kStringToDecimalHexTest },
        { "shutdown", "Shutdown And Reboot OS", kShutdown },
	{"strto","dummy",},
};                                     

//==============================================================================
//  ���� ���� �����ϴ� �ڵ�
//==============================================================================
/**
 *  ���� ���� ����
 */
void kStartConsoleShell( void )
{
    char vcCommandBuffer[ CONSOLESHELL_MAXCOMMANDBUFFERCOUNT ];
    int iCommandBufferIndex = 0;
    BYTE bKey;
    int iCursorX, iCursorY;
    char tmpcommand[11][30];
    
    // ������Ʈ ���
    kPrintf( CONSOLESHELL_PROMPTMESSAGE );
    int num=0;
    int n=0;
    while( 1 )
    {
	    
        // Ű�� ���ŵ� ������ ���
        bKey = kGetCh();
	if(bKey==KEY_DOWN)
	{

		bKey='\0';
		int i=0;
		if(0<=num&&num<9)
		{
		if(num!=n){	
			while(tmpcommand[num][i]!='\0')
			{
               		 kGetCursor( &iCursorX, &iCursorY );
               		 kPrintStringXY( iCursorX-1 , iCursorY, " " );
               		 kSetCursor( iCursorX - 1, iCursorY );

			i++;
			}
		}
		i=0;
		if(num<n)
		num++;
		kPrintf("%s",&tmpcommand[num]);
		while(1)
		{
			if(tmpcommand[num][i]=='\0')
			{
				iCommandBufferIndex=i;
				break;
			}
			vcCommandBuffer[i]=tmpcommand[num][i];
			i++;

		}
		}
		else if(num==9)
		{
			bKey='\0';
			kPrintf("%s",tmpcommand[num+1]);
		while(tmpcommand[num][i]!='\0')
		{
                kGetCursor( &iCursorX, &iCursorY );
                kPrintStringXY( iCursorX-1 , iCursorY, " " );
                kSetCursor( iCursorX - 1, iCursorY );
		
		i++;
		}
		i=0;
		while(1)
		{
			if(tmpcommand[num][i]=='\0')
			{
				iCommandBufferIndex=i;
				break;
			}
			vcCommandBuffer[i]=tmpcommand[num][i];
			i++;

		}
		}

	}
	else if(bKey== KEY_UP)
	{
		bKey='\0';
		int i=0;
		if(num>0&&num<10)
		{
		if(num!=n){	
		while(tmpcommand[num][i]!='\0')
		{
                kGetCursor( &iCursorX, &iCursorY );
                kPrintStringXY( iCursorX-1 , iCursorY, " " );
                kSetCursor( iCursorX - 1, iCursorY );
		i++;
		}
		}
		if(num>=1)
		num--;
		i=0;
		
		kPrintf("%s",&tmpcommand[num]);
		while(1)
		{
			if(tmpcommand[num][i]=='\0')
			{
				iCommandBufferIndex=i;
				break;
			}
			vcCommandBuffer[i]=tmpcommand[num][i];
			i++;

		}
		}
		else if(num==0)
		{
		while(tmpcommand[num][i]!='\0')
		{
                kGetCursor( &iCursorX, &iCursorY );
                kPrintStringXY( iCursorX , iCursorY, " " );
                kSetCursor( iCursorX - 1, iCursorY );
		i++;
		}
			bKey='\0';
			kPrintf("%s",&tmpcommand[num]);
		i=0;	
		while(1)
		{
			if(tmpcommand[num][i]=='\0')
			{
				iCommandBufferIndex=i;
				break;
			}
			vcCommandBuffer[i]=tmpcommand[num][i];
			i++;

		}
		}
	}
        // Backspace Ű ó��
	else if( bKey == KEY_BACKSPACE )
        {
            if( iCommandBufferIndex > 0 )
            {
                // ���� Ŀ�� ��ġ�� �� �� ���� ������ �̵��� ���� ������ ����ϰ� 
                // Ŀ�ǵ� ���ۿ��� ������ ���� ����
                kGetCursor( &iCursorX, &iCursorY );
                kPrintStringXY( iCursorX - 1, iCursorY, " " );
                kSetCursor( iCursorX - 1, iCursorY );
                iCommandBufferIndex--;
            }
        }
        // ���� Ű ó��
        else if( bKey == KEY_ENTER )
        {
            kPrintf( "\n" );
           kPrintf("%s",vcCommandBuffer);
            if( iCommandBufferIndex > 0 )
            {
		   
                // Ŀ�ǵ� ���ۿ� �ִ� ����� ����
                vcCommandBuffer[ iCommandBufferIndex ] = '\0';
		int u=0;
		int s=0;
		while(1)
		{
			if(vcCommandBuffer[u]=='\0'){
				tmpcommand[n][u]='\0';
			
				break;}
			tmpcommand[n][u]=vcCommandBuffer[u];
			u++;
		}
		
		if(n<=8){
			n++;
		num=n;}
		
                kExecuteCommand( vcCommandBuffer);
            }
            
            // ������Ʈ ��� �� Ŀ�ǵ� ���� �ʱ�ȭ
            kPrintf( "%s", CONSOLESHELL_PROMPTMESSAGE );            
            kMemSet( vcCommandBuffer, '\0', CONSOLESHELL_MAXCOMMANDBUFFERCOUNT );
            iCommandBufferIndex = 0;
        }
        // ����Ʈ Ű, CAPS Lock, NUM Lock, Scroll Lock�� ����
        else if( ( bKey == KEY_LSHIFT ) || ( bKey == KEY_RSHIFT ) ||
                 ( bKey == KEY_CAPSLOCK ) || ( bKey == KEY_NUMLOCK ) ||
                 ( bKey == KEY_SCROLLLOCK ) )
        {
            ;
        }
        else
        {
            // TAB�� �������� ��ȯ
            if( bKey == KEY_TAB )
            {
		    bKey='\0';
		    int icount;
   	 	icount = sizeof( gs_vstCommandTable ) / sizeof( SHELLCOMMANDENTRY );
		    int commandlength=0;
			int i=0;
			int check[icount];
			for(int j=0;j<icount;j++)
				check[j]=0;
   		 while(vcCommandBuffer[i]!='\0')
		 {
			 commandlength++;
			 i++;

		 }
		 i=0;

		for(int j=0;j<icount;j++)
		{
			for(int k=0;k<commandlength;k++)
			{
				if((vcCommandBuffer[k])== *(gs_vstCommandTable[j].pcCommand+k) ){
			//	kPrintf("%c",vcCommandBuffer[k]);
		//		kPrintf("%c",*(gs_vstCommandTable[j].pcCommand+k));
				check[j]++;
				}
			}
		}	
		int commandnum=0;
            	for(int j=0;j<icount;j++)
		{
			if(check[j]==commandlength)
			{
				commandnum++;
			}
		}
		if(commandnum==1){
			for(int j=0;j<icount;j++)
			{
				if(check[j]==commandlength)
				{
				//	kPrintf("%d",commandlength);
					int k=commandlength;
					while(*(gs_vstCommandTable[j].pcCommand+k)!='\0'){
				vcCommandBuffer[k]=*(gs_vstCommandTable[j].pcCommand+k);
					kPrintf("%c",*(gs_vstCommandTable[j].pcCommand+k));	
						k++;	
						}
					iCommandBufferIndex=k;
					
					}
		}
            }
		if(commandnum!=1)
		{
			char strcmp[commandnum][30];
			int index=0;
			for(int j=0;j<icount;j++)
			{
				if(check[j]==commandlength)
				{
					int leng=0;
					while(*(gs_vstCommandTable[j].pcCommand+leng)!='\0'){
			strcmp[index][leng]= *(gs_vstCommandTable[j].pcCommand+leng);
					leng++;}
					index++;
				}
			}
			int vertical=0;
			for(int j=commandlength;j<30;j++){
				for(int k=0;k<index-1;k++){
					    if(strcmp[k][j]==strcmp[k+1][j])
						vertical++;
							}
				if(vertical==index-1){

					kPrintf("%c",strcmp[0][j]);	
					vcCommandBuffer[j]=strcmp[0][j];
				}
				else
				{break;
				}
				vertical=0;
			}


		}


					





	//	kPrintf("sd%d",iCommandBufferIndex);
	    } 
            // ���ۿ� ������ �������� ���� ����
            if( iCommandBufferIndex < CONSOLESHELL_MAXCOMMANDBUFFERCOUNT )
            {
		kPrintf( "%c", bKey );
                vcCommandBuffer[ iCommandBufferIndex++ ] = bKey;
                if(bKey=='3')
		{
			kPrintf("fuc");
			kPrintf("%d",iCommandBufferIndex);
			kPrintf("%s",vcCommandBuffer);
		}
            }
        }
    }
}

/*
 *  Ŀ�ǵ� ���ۿ� �ִ� Ŀ�ǵ带 ���Ͽ� �ش� Ŀ�ǵ带 ó���ϴ� �Լ��� ����
 */
void kExecuteCommand( const char* pcCommandBuffer )
{
    int i, iSpaceIndex;
    int iCommandBufferLength, iCommandLength;
    int iCount;
    
    // �������� ���е� Ŀ�ǵ带 ����
    iCommandBufferLength = kStrLen( pcCommandBuffer );
    for( iSpaceIndex = 0 ; iSpaceIndex < iCommandBufferLength ; iSpaceIndex++ )
    {
        if( pcCommandBuffer[ iSpaceIndex ] == ' ' )
        {
            break;
        }
    }
    
    // Ŀ�ǵ� ���̺��� �˻��ؼ� ������ �̸��� Ŀ�ǵ尡 �ִ��� Ȯ��
    iCount = sizeof( gs_vstCommandTable ) / sizeof( SHELLCOMMANDENTRY );
    for( i = 0 ; i < iCount ; i++ )
    {
        iCommandLength = kStrLen( gs_vstCommandTable[ i ].pcCommand );
        // Ŀ�ǵ��� ���̿� ������ ������ ��ġ�ϴ��� �˻�
        if( ( iCommandLength == iSpaceIndex ) &&
            ( kMemCmp( gs_vstCommandTable[ i ].pcCommand, pcCommandBuffer,
                       iSpaceIndex ) == 0 ) )
        {
            gs_vstCommandTable[ i ].pfFunction( pcCommandBuffer + iSpaceIndex + 1 );
            break;
        }
    }

    // ����Ʈ���� ã�� �� ���ٸ� ���� ���
    if( i >= iCount )
    {
        kPrintf( "'%s' is not found.\n", pcCommandBuffer );
    }
}

/**
 *  �Ķ���� �ڷᱸ���� �ʱ�ȭ
 */
void kInitializeParameter( PARAMETERLIST* pstList, const char* pcParameter )
{
    pstList->pcBuffer = pcParameter;
    pstList->iLength = kStrLen( pcParameter );
    pstList->iCurrentPosition = 0;
}

/**
 *  �������� ���е� �Ķ������ ����� ���̸� ��ȯ
 */
int kGetNextParameter( PARAMETERLIST* pstList, char* pcParameter )
{
    int i;
    int iLength;

    // �� �̻� �Ķ���Ͱ� ������ ����
    if( pstList->iLength <= pstList->iCurrentPosition )
    {
        return 0;
    }
    
    // ������ ���̸�ŭ �̵��ϸ鼭 ������ �˻�
    for( i = pstList->iCurrentPosition ; i < pstList->iLength ; i++ )
    {
        if( pstList->pcBuffer[ i ] == ' ' )
        {
            break;
        }
    }
    
    // �Ķ���͸� �����ϰ� ���̸� ��ȯ
    kMemCpy( pcParameter, pstList->pcBuffer + pstList->iCurrentPosition, i );
    iLength = i - pstList->iCurrentPosition;
    pcParameter[ iLength ] = '\0';

    // �Ķ������ ��ġ ������Ʈ
    pstList->iCurrentPosition += iLength + 1;
    return iLength;
}
    
//==============================================================================
//  Ŀ�ǵ带 ó���ϴ� �ڵ�
//==============================================================================
/**
 *  �� ������ ���
 */
void kHelp( const char* pcCommandBuffer )
{
    int i;
    int iCount;
    int iCursorX, iCursorY;
    int iLength, iMaxCommandLength = 0;
    
    
    kPrintf( "=========================================================\n" );
    kPrintf( "                    MINT64 Shell Help                    \n" );
    kPrintf( "=========================================================\n" );
    
    iCount = sizeof( gs_vstCommandTable ) / sizeof( SHELLCOMMANDENTRY );

    // ���� �� Ŀ�ǵ��� ���̸� ���
    for( i = 0 ; i < iCount ; i++ )
    {
        iLength = kStrLen( gs_vstCommandTable[ i ].pcCommand );
        if( iLength > iMaxCommandLength )
        {
            iMaxCommandLength = iLength;
        }
    }
    
    // ���� ���
    for( i = 0 ; i < iCount ; i++ )
    {
        kPrintf( "%s", gs_vstCommandTable[ i ].pcCommand );
        kGetCursor( &iCursorX, &iCursorY );
        kSetCursor( iMaxCommandLength, iCursorY );
        kPrintf( "  - %s\n", gs_vstCommandTable[ i ].pcHelp );
    }
}

/**
 *  ȭ���� ���� 
 */
void kCls( const char* pcParameterBuffer )
{
    // �� ������ ����� ������ ����ϹǷ� ȭ���� ���� ��, ���� 1�� Ŀ�� �̵�
    kClearScreen();
    kSetCursor( 0, 1 );
}

/**
 *  �� �޸� ũ�⸦ ���
 */
void kShowTotalRAMSize( const char* pcParameterBuffer )
{
    kPrintf( "Total RAM Size = %d MB\n", kGetTotalRAMSize() );
}

/**
 *  ���ڿ��� �� ���ڸ� ���ڷ� ��ȯ�Ͽ� ȭ�鿡 ���
 */
void kStringToDecimalHexTest( const char* pcParameterBuffer )
{
    char vcParameter[ 100 ];
    int iLength;
    PARAMETERLIST stList;
    int iCount = 0;
    long lValue;
    
    // �Ķ���� �ʱ�ȭ
    kInitializeParameter( &stList, pcParameterBuffer );
    
    while( 1 )
    {
        // ���� �Ķ���͸� ����, �Ķ������ ���̰� 0�̸� �Ķ���Ͱ� ���� ���̹Ƿ�
        // ����
        iLength = kGetNextParameter( &stList, vcParameter );
        if( iLength == 0 )
        {
            break;
        }

        // �Ķ���Ϳ� ���� ������ ����ϰ� 16�������� 10�������� �Ǵ��Ͽ� ��ȯ�� ��
        // ����� printf�� ���
        kPrintf( "Param %d = '%s', Length = %d, ", iCount + 1, 
                 vcParameter, iLength );

        // 0x�� �����ϸ� 16����, �׿ܴ� 10������ �Ǵ�
        if( kMemCmp( vcParameter, "0x", 2 ) == 0 )
        {
            lValue = kAToI( vcParameter + 2, 16 );
            kPrintf( "HEX Value = %q\n", lValue );
        }
        else
        {
            lValue = kAToI( vcParameter, 10 );
            kPrintf( "Decimal Value = %d\n", lValue );
        }
        
        iCount++;
    }
}

/**
 *  PC�� �����(Reboot)
 */
void kShutdown( const char* pcParamegerBuffer )
{
    kPrintf( "System Shutdown Start...\n" );
    
    // Ű���� ��Ʈ�ѷ��� ���� PC�� �����
    kPrintf( "Press Any Key To Reboot PC..." );
    kGetCh();
    kReboot();
}
