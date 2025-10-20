#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    m_detected_points.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    bool h_line_raw[3][3] = {{false, false, false}, {true, true, true}, {false, false, false}};
    bool v_line_raw[3][3] = {{false, true, false}, {false, true, false}, {false, true, false}};
    bool d1_line_raw[3][3] = {{true, false, false}, {false, true, false}, {false, false, true}};
    bool d2_line_raw[3][3] = {{false, false, true}, {false, true, false}, {true, false, false}};

    CustomMatrix horizontal_pattern(h_line_raw);
    CustomMatrix vertical_pattern(v_line_raw);
    CustomMatrix diagonal1_pattern(d1_line_raw);
    CustomMatrix diagonal2_pattern(d2_line_raw);

    vector<CustomMatrix> targets;
    targets.push_back(horizontal_pattern);
    targets.push_back(vertical_pattern);
    targets.push_back(diagonal1_pattern);
    targets.push_back(diagonal2_pattern);

    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "image width " << image.width() << endl;
    cout << "image height " << image.height() << endl;

    //To not crash we set initial size of the matrix
    // vector<CustomMatrix> windows(image.width()*image.height());

    // Get the pixel value as an ARGB integer (QRgb is a typedef for unsigned int)
    for(int i = 1; i < image.width()-1;i++){
        for(int j = 1; j < image.height()-1;j++){
            bool local_window[3][3] = {false};

            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    QRgb rgbValue = image.pixel(i+m, j+n);
                    local_window[m+1][n+1] = (rgbValue != 0xffffffff);
                }
            }

            CustomMatrix mat(local_window);
            // windows.push_back(mat);

            for(const auto& target : targets){
                if(mat == target){
                    m_detected_points.append(QPoint(i, j));
                    break;
                }
            }
        }
    }
    cout << "Deteksi selesai. Ditemukan " << m_detected_points.size() << " segmen." << endl;
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4); // 4-pixel wide line
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        // Set the painter's pen to our custom pen.
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            //cout << m_points[i].x() << endl;
            painter.drawLine(m_points[i], m_points[i+1]);
        }
        isPaintLinesClicked = false;

        //return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }

    if (!m_detected_points.isEmpty()) {
        QPen purplePen(QColor(128, 0, 128));
        purplePen.setWidth(1);
        painter.setPen(purplePen);
        painter.setBrush(QBrush(QColor(128, 0, 128)));

        for (const QPoint& p : std::as_const(m_detected_points)) {
            painter.drawRect(p.x() - 4, p.y() - 4, 8, 8);
        }
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


