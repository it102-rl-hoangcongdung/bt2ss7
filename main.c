#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice dev;
    struct EnergySensor sensor;
    float operatingHours;
    float totalKWh = 0.0;
    float totalCost = 0.0;

    printf("=== MODULE QUAN LY PHONG THONG MINH ===\n");
    printf("Nhap ma thiet bi (ID): ");
    if (scanf("%d", &dev.deviceID) != 1) return 1;
    printf("Nhap ten thiet bi: ");
    if (scanf("%s", dev.deviceName) != 1) return 1;
    printf("Nhap trang thai (1: Bat, 0: Tat): ");
    if (scanf("%d", &dev.status) != 1) return 1;
    printf("Nhap cong suất đinh muc (kW): ");
    if (scanf("%f", &dev.ratedPowerKW) != 1) return 1;

    printf("Nhap dien ap đo được (V): ");
    if (scanf("%f", &sensor.voltageVolts) != 1) return 1;
    printf("Nhap dòng điên đo được (A): ");
    if (scanf("%f", &sensor.currentAmperes) != 1) return 1;
    printf("Nhap thời gian vắng người (phút): ");
    if (scanf("%d", &sensor.unoccupancyMinutes) != 1) return 1;

    printf("Nhap số giờ vận hành trong tháng (1 - 744): ");
    if (scanf("%f", &operatingHours) != 1) return 1;

    if (sensor.voltageVolts < 0 || sensor.currentAmperes < 0 || sensor.unoccupancyMinutes < 0) {
        printf("[LOI DU LIEU] Phat hien thong so cam bien bat thuong (gia tri am). Huy thao tac!\n");
        return 0;
    }

    if (operatingHours <= 0 || operatingHours > 744) {
        printf("[LOI DU LIEU] Số giờ vận hành trong tháng khong hop le (phai từ 1 đen 744 giờ). Từ chối tính toán!\n");
        return 0;
    }

    if (sensor.currentAmperes > 30.0) {
        dev.status = 0;
        printf("[CANH BAO AN TOAN] Dong dien vuot nguong an toan (> 30.0A). He thong ngat khan cap thiet bi! Nguy co chay no!\n");
    } else if (dev.status == 1 && sensor.unoccupancyMinutes >= 15) {
        dev.status = 0;
        printf("[TIET KIEM NANG LUONG] Phong trong lien tuc >= 15 phut. He thong tu đong tat thiet bi!\n");
    } else {
        printf("[TRANG THAI] Thiet bi hoat đong binh thuong va an toan.\n");
    }

    totalKWh = dev.ratedPowerKW * operatingHours;
    
    float remKWh = totalKWh;
    if (remKWh <= 50) {
        totalCost = remKWh * 1806;
    } else if (remKWh <= 100) {
        totalCost = 50 * 1806 + (remKWh - 50) * 1866;
    } else if (remKWh <= 200) {
        totalCost = 50 * 1806 + 50 * 1866 + (remKWh - 100) * 2167;
    } else {
        totalCost = 50 * 1806 + 50 * 1866 + 100 * 2167 + (remKWh - 200) * 2729;
    }

    printf("\n--- BAO CAO KET QUA ---\n");
    printf("Ma thiet bi: %d\n", dev.deviceID);
    printf("Ten thiet bi: %s\n", dev.deviceName);
    printf("Trang thai cuoi cung: %d (%s)\n", dev.status, dev.status == 1 ? "Đang bat" : "Đã tat");
    printf("Tong đien nang tieu thu: %.2f kWh\n", totalKWh);
    printf("Tong tien điên dự kiến (chua VAT): %.2f VNĐ\n", totalCost);

    return 0;
}
