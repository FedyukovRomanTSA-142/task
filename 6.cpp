import asyncio
import logging
from datetime import datetime, timedelta

# Настройка логирования
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class DataProcessor:
    def __init__(self):
        self._is_running = False
        self._current_task = None
        self._data_cache = {}
        self._cache_ttl = timedelta(minutes=10)

    async def start_processing(self):
        """Запуск обработки данных"""
        if self._is_running:
            logger.warning("Обработка уже запущена")
            return
        
        self._is_running = True
        try:
            self._current_task = asyncio.create_task(self._process_loop())
            logger.info("Обработка данных запущена")
        except Exception as e:
            logger.error(f"Ошибка при запуске: {e}")
            self._is_running = False

    async def stop_processing(self):
        """Остановка обработки данных"""
        if not self._is_running or not self._current_task:
            logger.warning("Обработка не запущена")
            return
        
        self._is_running = False
        try:
            await asyncio.wait_for(self._current_task, timeout=5.0)
            logger.info("Обработка данных остановлена")
        except asyncio.TimeoutError:
            logger.warning("Таймаут при остановке обработки")
        except Exception as e:
            logger.error(f"Ошибка при остановке: {e}")
        finally:
            self._current_task = None

    async def _process_loop(self):
        """Основной цикл обработки"""
        while self._is_running:
            try:
                await self._fetch_data()
                await self._cleanup_cache()
                await asyncio.sleep(1)
            except asyncio.CancelledError:
                break
            except Exception as e:
                logger.error(f"Ошибка в цикле обработки: {e}")
                await asyncio.sleep(5)

    async def _fetch_data(self):
        """Получение и обработка данных"""
        try:
            # Имитация получения данных
            data = await self._get_external_data()
            
            if not data:
                logger.debug("Данные не получены")
                return
            
            processed_data = await self._transform_data(data)
            await self._store_data(processed_data)
            
        except ValueError as e:
            logger.warning(f"Некорректные данные: {e}")
        except ConnectionError as e:
            logger.error(f"Ошибка соединения: {e}")
            await asyncio.sleep(2)
        except Exception as e:
            logger.error(f"Неожиданная ошибка при получении данных: {e}")

    async def _get_external_data(self):
        """Имитация получения внешних данных"""
        await asyncio.sleep(0.1)
        return {"timestamp": datetime.now(), "value": 42}

    async def _transform_data(self, data):
        """Преобразование данных"""
        if not isinstance(data, dict):
            raise ValueError("Данные должны быть словарем")
        
        if "value" not in data:
            raise ValueError("Отсутствует обязательное поле 'value'")
        
        transformed = {
            "processed_value": data["value"] * 2,
            "processed_at": datetime.now(),
            "source_timestamp": data.get("timestamp")
        }
        
        return transformed

    async def _store_data(self, data):
        """Сохранение данных в кэш"""
        try:
            if not data:
                return
            
            key = str(data["processed_at"].timestamp())
            self._data_cache[key] = {
                "data": data,
                "created_at": datetime.now()
            }
            
        except KeyError as e:
            logger.error(f"Отсутствует ключ в данных: {e}")
        except Exception as e:
            logger.error(f"Ошибка при сохранении данных: {e}")

    async def _cleanup_cache(self):
        """Очистка устаревших данных из кэша"""
        try:
            current_time = datetime.now()
            expired_keys = [
                key for key, value in self._data_cache.items()
                if current_time - value["created_at"] > self._cache_ttl
            ]
            
            for key in expired_keys:
                del self._data_cache[key]
                
            if expired_keys:
                logger.debug(f"Удалено устаревших записей: {len(expired_keys)}")
                
        except RuntimeError as e:
            logger.error(f"Ошибка при изменении кэша: {e}")
        except Exception as e:
            logger.error(f"Неожиданная ошибка при очистке кэша: {e}")

    def get_processing_stats(self):
        """Получение статистики обработки"""
        return {
            "is_running": self._is_running,
            "cache_size": len(self._data_cache),
            "cache_ttl_minutes": self._cache_ttl.total_seconds() / 60
        }

async def main():
    """Основная функция"""
    processor = DataProcessor()
    
    try:
        await processor.start_processing()
        await asyncio.sleep(5)
        
        stats = processor.get_processing_stats()
        logger.info(f"Статистика: {stats}")
        
        await asyncio.sleep(2)
        
    except KeyboardInterrupt:
        logger.info("Получен сигнал прерывания")
    finally:
        await processor.stop_processing()

if __name__ == "__main__":
    asyncio.run(main())
