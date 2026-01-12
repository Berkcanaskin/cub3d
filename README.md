# cub3d - 3D Raycasting Oyun Motoru

## 📚 Proje Açıklaması

**cub3d**, Wolfenstein 3D tarzı raycasting teknolojisini kullanarak 3D oyun ortamı oluşturan projedir. Bu proje, 3D grafik programlaması, matematik, veri yapıları ve performans optimizasyonunu öğretir.

## 🎯 Oyun Mekanikları

### Oyun Amacı
- 3D labirent ortamında hareket etmek
- Duvar dokularını görmek
- Mini-map sistemi kullanarak navigasyon

### Kontroller
```
W veya ↑ - İleri hareket
S veya ↓ - Geri hareket
A        - Sola dön
D        - Sağa dön
← →      - Kamera açısını değiştir
ESC      - Oyundan çık
```

## 🛠️ Raycasting Teknolojisi

### Raycasting Nedir?
Raycasting, 2D haritasından 3D perspektif görüş oluşturan bir tekniktir. Her ekran sütunu için:

```
1. Kameradan ışın gönder
2. Duvarla kesişim noktasını bul
3. Kesişim uzaklığını hesapla
4. Duvar yüksekliğini hesapla (uzaklığa göre)
5. Doku koordinatını belirle
6. Sütunu dokulu duvarla çiz
```

### Matematiksel Temeller

#### Işın-Duvar Kesişimi
```
Kamera Pozisyonu: (cam_x, cam_y)
Işın Yönü: angle

Duvar Noktası: (wall_x, wall_y)
Kesişim Uzaklığı: distance = sqrt((wall_x - cam_x)² + (wall_y - cam_y)²)
```

#### Doku Ataması
```
Duvar dokusundaki pixel = distance % texture_width
```

#### Perspektif Korreksiyon
```
Fiş-eye distortion önlemek için:
corrected_distance = raw_distance * cos(ray_angle - camera_angle)
```

## 📖 Dosya Yapısı

```
cub3d/
├── source/
│   ├── main.c               # Entry point
│   ├── parser.c             # .cub dosya parsing
│   ├── map_validation.c     # Harita kontrolü
│   ├── init_game.c          # Oyun başlatma
│   ├── raycasting.c         # Raycasting motoru
│   ├── render.c             # Rendering
│   ├── texture.c            # Doku yönetimi
│   ├── input.c              # Input handling
│   ├── movement.c           # Kamera hareketi
│   ├── utils.c              # Yardımcı fonksiyonlar
│   └── cleanup.c            # Kaynakları serbest bırakma
├── includes/
│   ├── cub3d.h
│   └── defines.h
├── map.cub                  # Örnek harita dosyası
├── textures/                # Doku dosyaları (PNG/XPM)
│   ├── north.xpm
│   ├── south.xpm
│   ├── east.xpm
│   ├── west.xpm
│   └── floor.xpm
├── minilibx-linux/
├── Makefile
└── Makefile.rules
```

## 🛠️ .cub Dosya Formatı

```
# Zoom seviyesi (bonus)
R 800 600

# Doku dosyaları
NO ./textures/north.xpm
SO ./textures/south.xpm
EA ./textures/east.xpm
WE ./textures/west.xpm
S ./textures/sprite.xpm

# Renkler (RGB)
F 220,100,0
C 225,30,0

# Harita (1: duvar, 0: boş, N/S/E/W: oyuncu pozisyonu ve yönü)
111111111111111111111
100000000110000000001
101000000010000000001
1000000000000N0000001
111111111111111111111
```

## 📚 Temel Konseptler

### 1. Harita Yapısı
```c
typedef struct s_map {
    char **grid;           // 2D harita
    int width;
    int height;
    int player_x;
    int player_y;
    int player_angle;      // Radyan cinsinden
} t_map;
```

### 2. Raycasting Motorunun Çekirdeği

```c
void cast_rays(t_game *game)
{
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        // Her ekran sütunu için ışın gönder
        float ray_angle = game->player_angle - FOV/2 + (x / WINDOW_WIDTH) * FOV;
        
        // Işın-duvar kesişim noktasını bul
        float distance = find_wall_distance(game, ray_angle);
        
        // Perspektif koreksiyonu
        distance *= cos(ray_angle - game->player_angle);
        
        // Duvar yüksekliğini hesapla
        int wall_height = (WINDOW_HEIGHT * TILE_SIZE) / distance;
        
        // Duvar dokusunu ata
        int texture_x = get_texture_x(game, ray_angle, distance);
        
        // Sütunu çiz
        draw_wall_column(game, x, wall_height, texture_x);
    }
}
```

### 3. DDA Algoritması (Işın Takip)

```c
// DDA: Digital Differential Analyzer
// Işını grid içinde takip et

float current_x = player_x;
float current_y = player_y;
float step_x = cos(ray_angle);
float step_y = sin(ray_angle);

while (!is_wall(map, current_x, current_y))
{
    current_x += step_x;
    current_y += step_y;
}

float distance = sqrt((current_x - player_x)² + (current_y - player_y)²);
```

## 🎯 Teknik Zorluklar

### 1. Doku Haritalaması
```
Işın duvarı nerede vurdu?
- North/South duvarı: x koordinatını doku width'ine map et
- East/West duvarı: y koordinatını doku height'ine map et

Hangi doku seviyesi kullanılacak?
- Kamera açısına göre duvar yönünü belirle
- Uygun doku dosyasını yükle
```

### 2. Performans
```
60 FPS'de 800x600 çözünürlükte çalışması gerekir
-> Her pixel için ray casting = pahalı
-> Optimizasyon: Pre-calculated lookup tables
-> Hızlı doku yükleme: XPM formatını parse et
```

### 3. Fiş-Eye Distortion
```
Düz raycasting'de kenarlar eğri görünür
Çözüm: ray_distance *= cos(ray_angle - camera_angle)
```

## 📚 Öğrenme Çıktıları

✅ 3D grafik programlaması öğrenildi  
✅ Raycasting algoritması mastered  
✅ Işın-duvar kesişim matematiği anlaşıldı  
✅ Doku haritalaması implementasyonu yapıldı  
✅ Perspektif koreksiyonu uygulandı  
✅ Gerçek zamanlı rendering optimizasyonu öğrenildi  
✅ MiniLibX ileri kullanımı yapıldı  

## 💡 Temel Matematik

### Açı Dönüştürme
```c
float radians = degrees * (M_PI / 180.0);
float degrees = radians * (180.0 / M_PI);
```

### Trigonometrik Fonksiyonlar
```c
float x = cos(angle);  // Yatay bileşen
float y = sin(angle);  // Dikey bileşen
```

### Vektör İşlemleri
```c
// Mesafe
float dist = sqrt(dx*dx + dy*dy);

// Normalize
float len = sqrt(x*x + y*y);
x /= len;
y /= len;
```

## 🚀 Bonus Özellikler (İsteğe Bağlı)

- **Wall Sprites**: Duvar dokularının yanında sprite'lar
- **Floor/Ceiling Texture**: Yer ve tavan dokularını render et
- **Mouse Look**: Fare ile kamera kontrolü
- **Minimap**: 2D harita gösterir
- **Door System**: Açılıp kapanan kapılar
- **Enemy AI**: AI düşmanlar
- **Animation**: Hareket animasyonları

## 🔧 Derleme

```bash
cd cub3d
make                    # cub3d binary'i oluştur

./cub3d map.cub         # Oyunu başlat
```

## 📝 Norm Standartları

- 80 karaktere kadar satır uzunluğu
- Fonksiyon başına maksimum 25 satır
- Memory leaks yoktur
- Norm compliance sağlanmıştır

## 💡 Key Learning Points

1. **3D Graphics**: Raycasting tekniklerinin temelleri
2. **Game Mathematics**: Trigonometri ve vektör matematiği
3. **Texture Mapping**: 2D dokuyu 3D'ye projeksiyonu
4. **Performance Optimization**: Real-time rendering
5. **File Parsing**: Kompleks dosya formatlarını parse etme
6. **Memory Management**: Büyük veri yapıları ile çalışma

Bu proje, 3D grafik programlamasına giriş sağlar ve oyun geliştirme temelleri oluşturur.
