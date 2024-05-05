#include "HAL_Flash_Driver.h"
#include "HAL_RCC_Driver.h"

/*****************************************************************************/
/*                       Helper Functions                                    */
/*****************************************************************************/


/*****************************************************************************/
/*                       Driver Exposed HAL                                  */
/*****************************************************************************/
/*! \brief  Unlocks the FLASH control register access
 */
void HAL_Flash_Unlock(void)
{
    FLASH->KEYR = FLASH_KEYR_1;
    FLASH->KEYR = FLASH_KEYR_2;
}
    
/*! \brief  Locks the FLASH control register access
 */
void HAL_Flash_Lock(void)
{
    FLASH->CR |= FLASH_CR_LOCK;
}

/*! \brief Perform a mass erase or erase the specified FLASh memory sectors.
 *         This is a blocking operation
 *  \param  *pEraseInit     pointer to a erase configuration structure
 *  \param  *SectorError    pointer to variable that contains the config on
 *                          faulty sector in case of error.
 *                          0xFFFFFFFFU means that all the sectors have been
 *                          correctly erased
 */
void HAL_Flash_Erase(Flash_EraseInitTypeDef *pEraseInit, uint32_t *SectorError)
{
    uint8_t i;
    uint8_t sectorNumber;
    
    // wait to make sure that no flash operation is ongoing
    while(FLASH->SR & FLASH_SR_BSY);    
    FLASH->CR |= pEraseInit->TypeErase;
    
    if(pEraseInit->TypeErase == HAL_FLASH_TYPEERASE_SECTOR)
    {
        // Check to make sure that that number of sectors to erase is valid
        if( (pEraseInit->NbSectors < 1) || 
            (pEraseInit->NbSectors > (8 - pEraseInit->Sector)))
        {
            // Error
            return;
        }
        
        for(i = 0; i < pEraseInit->NbSectors; i++)
        {
            sectorNumber = pEraseInit->Sector + i;
            FLASH->CR |= (sectorNumber << FLASH_CR_SNB_Pos);
            FLASH->CR |= FLASH_CR_STRT; // Start Erase
            while(FLASH->SR & FLASH_SR_BSY);    // Wait til finish
        }
    }
    else
    {
        FLASH->CR |= FLASH_CR_STRT; // Start Erase
        // Wait until the operation is completed
        while(FLASH->SR & FLASH_SR_BSY);    
    }
    
    // Clear erase bits
    FLASH->CR &= ~(FLASH_CR_MER | FLASH_CR_SER);
}

/*! \brief Program byte, halfword, word, or double word at a specified address
 *          
 *  \param  typeProgram indicate the way to program at a specified address.
 *                      Value can be of FLASH Type Program
 *                      At the moment, only supports BYTE type programming
 *  \param  address     specifies the address to be programmed
 *  \param  data        spexifies the data to be programmed
 */
void HAL_Flash_Program(uint32_t typeProgram, uint32_t address, uint8_t data)
{
    while(FLASH->SR & FLASH_SR_BSY);    // Make sure flash is not busy
    
    FLASH->CR |= FLASH_CR_PG;           // Set Flashing Programming bit
    FLASH->CR |= FLASH_TYPEPROGRAM_BYTE;// Configure the PSIZE parallelism
    *(__IO uint8_t*) address = data;
    while(FLASH->SR & FLASH_SR_BSY);    // Wait until flash operation is complete
    FLASH->CR &= ~FLASH_CR_PG;          // Disable flash programming
}
